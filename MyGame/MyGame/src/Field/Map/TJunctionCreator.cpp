#include "TJunctionCreator.h"
#include"../../Resource/CsvReader.h"
#include "../../Graphic/Shader/ShaderManager.h"
#include "../../Graphic/Model.h"
#include "../../Graphic/Sprite.h"
#include "../../Graphic/Shader/CBuff/Floor_CB.h"

TJunctionCreator::TJunctionCreator()
{
}

void TJunctionCreator::load(std::map<BuildingGroup, BuildingPtr>& buildingPairList,const std::string& buildingmap, const std::string& tilemap)
{
	buildings_.clear();
	ftm_.initialize(tilemap);
	CsvReader reader{ buildingmap };

	for (int z = 0; z < reader.rows(); z++) {

		for (int x = 0; x < reader.columns(); x++) {

			auto data = reader.get(z, x);
			auto position = data.find("_");

			if (std::string::npos == position)
			{
				continue;
			}

			int type = atoi(data.substr(0, position).c_str());

			if (type == 0)continue;

			char dirC = data.substr(++position).front();
			int dir = atoi(&dirC);
			//dataList_.push_back(std::make_pair(type, dir));

			BuildingPtr tempPtr = buildingPairList[static_cast<BuildingGroup>(type)]->clone(nullptr, x, reader.rows() - z, dir);

			buildings_.push_back(tempPtr);

		}
		//outputfile << "\n";
	}
}

void TJunctionCreator::setFloor(MODEL_ID modelid)
{
	_modelid = modelid;
}

void TJunctionCreator::draw(const Vector3& position, float angle, bool isUseTileMap) const
{
	for (auto& b : buildings_) {
		Matrix drawPose = b->getPose();
		drawPose *= Matrix::CreateRotationY(angle);
		drawPose *= Matrix(Matrix::Identity).Translation(position);
		b->getAnimation().Draw(drawPose);
	}
	if (isUseTileMap) {
		auto cbuffid = ShaderManager::getInstance().getCBuff(ShaderID::TILING_SHADER);
		Floor_CB* fcb = (Floor_CB*)GetBufferShaderConstantBuffer(cbuffid);


		fcb->gridSize = 16.5f;
		fcb->maxXSize = 495.0f;
		fcb->maxYSize = 462.0f;
		fcb->columnSize = 30;

		for (int i = 0; i < CELLTYPE_SIZE; i++) {
			fcb->celltype[i].x = ftm_.get(i * 4);
			fcb->celltype[i].y = ftm_.get(i * 4 + 1);
			fcb->celltype[i].z = ftm_.get(i * 4 + 2);
			fcb->celltype[i].w = ftm_.get(i * 4 + 3);
		}

		//ShaderManager::getInstance().UpdateCBuff<Floor_CB>(ShaderID::TILING_SHADER, cb, 3);

		UpdateShaderConstantBuffer(cbuffid);
		SetShaderConstantBuffer(cbuffid, DX_SHADERTYPE_PIXEL, 3);

		ShaderManager::getInstance().begin(ShaderID::TILING_SHADER);
		SetUseTextureToShader(0, Sprite::GetInstance().GetHandle(SPRITE_ID::SPRITE_TEXTURE));
	}
	Matrix mapMat = Matrix(Matrix::Identity)*Matrix::CreateRotationY(angle);
	mapMat = mapMat.Translation(position);
	Model::GetInstance().Draw(_modelid, mapMat);

	if(isUseTileMap)ShaderManager::getInstance().end();

}
