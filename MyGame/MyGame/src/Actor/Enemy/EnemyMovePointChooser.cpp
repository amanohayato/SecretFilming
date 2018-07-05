#include "EnemyMovePointChooser.h"
#include "../../World/IWorld.h"
#include "../../Field/WalkMap.h"
#include "../../Math/Random.h"
#include "../../Field/WalkPath.h"
#include <assert.h>

// エネミー用～移動座標指定クラス
// 制作者：Ho Siu Ki（何兆祺）

// コンストラクタ
EnemyMovePointChooser::EnemyMovePointChooser(IWorld* world, const Vector3& position, int walk_sheet_type)
	: world_(world), walk_sheet_type_(walk_sheet_type)
{
	set_point(position);
}

// 現在のポイントを設定
void EnemyMovePointChooser::set_point(const Vector3& position)
{
	current_point_ = world_->getWalkMap().getNearestNode(walk_sheet_type_, position);
	goal_ = current_point_;
}

// 次の目的地を決定（ランダム）
void EnemyMovePointChooser::choose_goal()
{
	current_point_ = goal_;
	int goal = Random::GetInstance().Range(0, (int)world_->getWalkMap().node_count(walk_sheet_type_) - 2);
	if (goal < goal_)goal_ = goal;
	else goal_ = goal + 1;

	auto path = WalkPath::find_path(world_->getWalkMap(), walk_sheet_type_, current_point_, goal_);
	path_.clear();
	path_.assign(path.rbegin(), path.rend());
}

// 次のポイントを取得
int EnemyMovePointChooser::get_next_point() const
{
	assert(!path_.empty());
	return path_.front();
}

// 
Vector3 EnemyMovePointChooser::operator()(const Vector3& position, bool& is_end)
{
	is_end = false;
	Vector3 next = world_->getWalkMap().getNode(walk_sheet_type_, get_next_point()).position;	// 次の目的地を取得
	next.y = position.y;				// y軸は無視
	if (Vector3::Distance(position, next) <= 10.0f)		// 目的地に到達したら
	{
		if (path_.front() == goal_)						// 最終目的地に到達したら
		{
			is_end = true;				// 終了を教えて
			return position;			// 移動しない
		}
		path_.erase(path_.begin());		// 次の目的地へ移動
	}
	return world_->getWalkMap().getNode(walk_sheet_type_, get_next_point()).position;			// 次の目的地を渡す
}