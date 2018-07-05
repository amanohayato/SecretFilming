#ifndef BUILDING_PTR_H_
#define BUILDING_PTR_H_

#include<memory>

class BuildingBase;
using BuildingPtr = std::shared_ptr<BuildingBase>;

// Œš•¨‚Ì¶¬
template <class T, class... Args>
inline BuildingPtr new_building(Args&&... args) {
	return std::make_shared<T>(args...);
}

#endif // !BUILDING_PTR_H_