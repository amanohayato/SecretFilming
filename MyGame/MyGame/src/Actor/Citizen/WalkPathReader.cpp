#include "WalkPathReader.h"
#include"../../Resource/CsvReader.h"

WalkPathReader::WalkPathReader()
{
}

void WalkPathReader::initialize()
{
	pathList_citizen_.clear();
	pathList_car_.clear();
	pathList_police_.clear();
}
//市民移動ルートCSV読み込み
void WalkPathReader::load_citizenmap(const std::string & sheetName1, const std::string & sheetName2, const std::string & sheetName3, const std::string & sheetName4, const std::string & sheetName5, const std::string & sheetName6)
{
	std::list<std::string>namelist = { sheetName1,sheetName2 ,sheetName3 ,sheetName4 ,sheetName5 ,sheetName6 };
	for (auto at : namelist)
	{
		auto clist = load(at);
		pathList_citizen_.push_back(clist);
	}
}
//車移動ルートCSV読み込み
void WalkPathReader::load_carmap(const std::string & sheetName1, const std::string & sheetName2, const std::string & sheetName3, const std::string & sheetName4, const std::string& sheetName5, const std::string& sheetName6, const std::string& sheetName7)
{
	std::list<std::string>namelist = { sheetName1,sheetName2 ,sheetName3 ,sheetName4 ,sheetName5 ,sheetName6,sheetName7 };
	for (auto at : namelist)
	{
		auto clist = load(at);
		pathList_car_.push_back(clist);
	}
}
//警官移動ルートCSV読み込み
void WalkPathReader::load_policemap(const std::string & sheetName)
{
	/*
	std::vector<std::string>namelist = { sheetName };
	for (auto at : namelist)
	{
	auto plist = load(at);
	pathList_police_.push_back(plist);
	}
	*/
	auto plist = loadVector(sheetName);
	pathList_police_.push_back(plist);
}

//取得
std::list<Vector3> WalkPathReader::getWalkList(int sheet)
{
	return pathList_citizen_[sheet];
}

std::list<Vector3> WalkPathReader::getDriveList(int sheet)
{
	return pathList_car_[sheet];
}

std::vector<Vector3> WalkPathReader::getPoliceWalkList(int sheet)
{
	return pathList_police_[sheet];
}
//CSVをVector3化(戻り値list)
std::list<Vector3> WalkPathReader::load(const std::string & sheetName)
{
	std::list<Vector3> result{};
	CsvReader reader{ sheetName };
	for (int i = 0; i < reader.rows(); i++) {
		Vector3 target;
		target.x = reader.getf(i, 0);
		target.y = reader.getf(i, 1);
		target.z = reader.getf(i, 2);

		result.push_back(target);
	}
	return result;
}
//CSVをVector3化(戻り値vector)
std::vector<Vector3> WalkPathReader::loadVector(const std::string & sheetName)
{
	std::vector<Vector3> result{};
	CsvReader reader{ sheetName };
	for (int i = 0; i < reader.rows(); i++) {
		Vector3 target;
		target.x = reader.getf(i, 0);
		target.y = reader.getf(i, 1);
		target.z = reader.getf(i, 2);

		result.push_back(target);
	}
	return result;
}
