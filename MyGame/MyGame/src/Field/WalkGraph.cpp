#include "WalkGraph.h"
#include<assert.h>
#include"../Resource/CsvReader.h"

#define SHEET_OUT_OF_LENGTH assert(sheet < currentSheet_)
bool LineAndLine(float A1x, float A1y, float A2x, float A2y, float B1x, float B1y, float B2x, float B2y) {
	{
		const float baseX = B2x - B1x;
		const float baseY = B2y - B1y;
		const float sub1X = A1x - B1x;
		const float sub1Y = A1y - B1y;
		const float sub2X = A2x - B1x;
		const float sub2Y = A2y - B1y;

		const float bs1 = baseX * sub1Y - baseY * sub1X;
		const float bs2 = baseX * sub2Y - baseY * sub2X;
		const float re = bs1 * bs2;
		if (re > 0) {
			return false;
		}
	}
	{
		const float baseX = A2x - A1x;
		const float baseY = A2y - A1y;
		const float sub1X = B1x - A1x;
		const float sub1Y = B1y - A1y;
		const float sub2X = B2x - A1x;
		const float sub2Y = B2y - A1y;

const float bs1 = baseX * sub1Y - baseY * sub1X;
const float bs2 = baseX * sub2Y - baseY * sub2X;
const float re = bs1 * bs2;
if (re > 0) {
	return false;
}
	}
	return true;
}
bool RectAndLine(float left, float top, float right, float bottom, float x1, float y1, float x2, float y2) {
	if (LineAndLine(left, top, right, top, x1, y1, x2, y2)) { return true; }
	if (LineAndLine(right, top, right, bottom, x1, y1, x2, y2)) { return true; }
	if (LineAndLine(right, bottom, left, bottom, x1, y1, x2, y2)) { return true; }
	if (LineAndLine(left, bottom, left, top, x1, y1, x2, y2)) { return true; }

	return false;
}
bool collision_Box_Line_2D(const Vector3& position, float width, float height, const Vector3& start, const Vector3& end) {
	float left = position.x - (width*0.5f);
	float right = position.x + (width*0.5f);
	float top = position.z + (height*0.5f);
	float bottom = position.z - (height*0.5f);
	return RectAndLine(left, top, right, bottom, start.x, start.z, end.x, end.z);
}

void WalkGraph::initialize() {
	nodes_.clear();
	node_edge_connect_list_.clear();
	currentSheet_ = 0;
	indexNum_ = 0;
}

void WalkGraph::load(const std::string & pointfilename, const std::string & pathfilename) {
	currentSheet_++;//シートのカウントを追加
	CsvReader reader(pointfilename);//ポイントの読み込み

	nodes_.emplace_back();//新しいシートの作成
	int nodeSize = reader.rows();//ノード数の確認

	nodes_.back().resize(nodeSize);//ノード数分配列サイズを確保


	for (int i = 0; i < nodeSize; i++) {
		//ポイント位置の設定
		nodes_.back()[i].position.x = reader.getf(i, 0);
		nodes_.back()[i].position.y = 10.0f;// reader.getf(i, 1);
		nodes_.back()[i].position.z = reader.getf(i, 1);
	}

	reader.load(pathfilename);//エッジの読み込み
	int edgeSize = reader.rows();//エッジ数の確認

								 //エッジデータの読み込み
	for (int i = 0; i < edgeSize; i++) {
		//始点終点のノード番号を読み込む
		int start = reader.geti(i, 0);
		int end = reader.geti(i, 1);
		float cost = Vector3::Distance(nodes_.back()[start].position, nodes_.back()[end].position);//距離をエッジのコストとする
																								   //相互に相手を行き先として設定する
		nodes_.back()[start].edges.push_back({ end,cost });
		nodes_.back()[end].edges.push_back({ start,cost });
	}
}

//ノードを取得

const WalkGraph::Node & WalkGraph::getNode(int sheet, int index) const {
	SHEET_OUT_OF_LENGTH;
	return nodes_.at(sheet)[index];
}

//ノード数を取得

std::size_t WalkGraph::node_count(int sheet) const {
	SHEET_OUT_OF_LENGTH;
	return nodes_.at(sheet).size();
}

int WalkGraph::getNearestNode(int sheet, const Vector3& position) const
{
	SHEET_OUT_OF_LENGTH;
	int result = 0;
	float nearlength = Vector3::Distance(position, nodes_.at(sheet).front().position);

	float length;
	for (int i = 0; i < nodes_.at(sheet).size(); i++) {
		length = Vector3::Distance(position, nodes_.at(sheet).at(i).position);
		if (length < nearlength) {
			nearlength = length;
			result = i;
		}
	}
	return result;
}

int WalkGraph::clearEdge(int sheet, const Vector3 & position, int width, int height)
{
	if (nodes_.empty())return -1;//エラー

	node_edge_connect_list_.emplace_back();

	int count = 0;
	for (auto& n : nodes_[sheet]) {

		for (auto& e : n.edges) {
			if (collision_Box_Line_2D(position, (float)width, (float)height, n.position, nodes_.at(sheet).at(e.node).position)) {
				node_edge_connect_list_.back().push_back(std::make_tuple(count, e.node, e.cost));
				//node_edge_connect_list_.back().push_back(std::make_pair(e.node, count));
			}
		}
		count++;
	}
	for (auto& nel : node_edge_connect_list_) {
		for (auto& ne : nel) {
			auto pos = std::remove_if(nodes_[sheet][std::get<0>(ne)].edges.begin(), nodes_[sheet][std::get<0>(ne)].edges.end(), [&](auto& edg) {return edg.node == std::get<1>(ne); });
			nodes_[sheet][std::get<0>(ne)].edges.erase(pos, nodes_[sheet][std::get<0>(ne)].edges.end());
		}
	}

	return (int)node_edge_connect_list_.size() - 1;
 }

 void WalkGraph::createEdge(int sheet, int indexNum)
 {
	 if (indexNum <= 0)return;

	 for (auto& necl : node_edge_connect_list_) {
		 for (auto& nec : necl) {
			 Edge e;
			 e.cost = std::get<2>(nec);
			 e.node = std::get<1>(nec);
			 nodes_[sheet][std::get<0>(nec)].edges.push_back(e);
		 }
	 }
 }
