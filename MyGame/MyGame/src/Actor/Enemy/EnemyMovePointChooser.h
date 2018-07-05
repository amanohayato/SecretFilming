#ifndef ENEMY_MOVE_POINT_CHOOSER_H_
#define ENEMY_MOVE_POINT_CHOOSER_H_

#include "../../Math/Vector3.h"
#include <vector>

class IWorld;

// エネミー用～移動座標指定クラス
// 制作者：Ho Siu Ki（何兆祺）

class EnemyMovePointChooser
{
public:
	// コンストラクタ
	EnemyMovePointChooser(IWorld* world, const Vector3& position, int walk_sheet_type);
	// 現在のポイントを設定
	void set_point(const Vector3& position);
	// 次の目的地を決定（ランダム）
	void choose_goal();
	// 次のポイントを取得
	int get_next_point()const;
	// 
	Vector3 operator()(const Vector3& position, bool& is_end);

private:
	int walk_sheet_type_;	// 巡回する対象シート
	IWorld* world_;
	int current_point_;		// 今回の経路の開始地点
	int goal_;				// 目的地点
	std::vector<int> path_;	// 移動ルート
};

#endif // !ENEMY_MOVE_POINT_CHOOSER_H_