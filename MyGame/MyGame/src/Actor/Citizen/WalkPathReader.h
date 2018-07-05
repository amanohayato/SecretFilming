#pragma once
#include<string>
#include<vector>
#include<list>
#include"../../Math/Vector3.h"

class WalkPathReader {
	WalkPathReader();
public:
	static WalkPathReader& getInstance() {
		static WalkPathReader wpr;
		return wpr;
	}

	void initialize();
	void load_citizenmap(const std::string & sheetName1, const std::string & sheetName2, const std::string & sheetName3, const std::string & sheetName4, const std::string & sheetName5, const std::string & sheetName6);
	void load_carmap(const std::string& sheetName1, const std::string& sheetName2, const std::string& sheetName3, const std::string& sheetName4, const std::string& sheetName5, const std::string& sheetName6, const std::string& sheetName7);
	void load_policemap(const std::string& sheetName);
	std::list<Vector3> getWalkList(int sheet);
	std::list<Vector3> getDriveList(int sheet);
	std::vector<Vector3> getPoliceWalkList(int sheet);

private:
	std::list<Vector3> load(const std::string& sheetName);
	std::vector<Vector3> loadVector(const std::string& sheetName);
private:
	std::vector<std::list<Vector3>> pathList_citizen_;
	std::vector<std::list<Vector3>> pathList_car_;
	std::vector<std::vector<Vector3>> pathList_police_;
};