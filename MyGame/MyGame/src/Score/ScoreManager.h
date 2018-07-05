#pragma once
#include"../Math/MathHelper.h"
#include"../Math/Math.h"
#include"../Camera/Camera.h"
#include"../Math/Matrix.h"
#include"../Math/Vector3.h"
#include"../Math/Vector2.h"
#include"../Actor/Player/Base/MatrixRotation.h"

class ScoreManager {
	ScoreManager();

	void ScoreDistance(Vector3 player, Vector3 enemy) {
		float d = Vector3::Distance(player, enemy);
		if ( d < distance.x) {
			dis = 1.0f;
		}
		else if (d > distance.y) {
			dis = 0.0f;
		}
		else {
			d = distance.y - d;
			MathHelper::Lerp(0.0f, 1.0f, d / distance.x);
		}
	};

	void ScorePart(Vector3 playerpPos,Vector3 partPos) {
		Vector3 target = Camera::GetInstance().Target.Get();
		Vector3 vector0 = target - playerpPos;
		Vector3 vector1 = partPos - playerpPos;
		float angle = Vector3::Angle(vector0, vector1);
		part = MathHelper::Abs(angle);
	};

	void ScoreAngle(float centerAngle, float rightAngle,float leftAngle) {
		constexpr float maxangle{ 360.0f };
		float player_y = MatrixRotation::Angle(playerrotation_).y;
		if (player_y < 0.0f) {
			player_y += 360.0f;
		}
		centerAngle = fmodf(centerAngle + MatrixRotation::Angle(enemyRotation_).y,maxangle);
	};

	int GetScore(int basicScore) {
		float score_ = ((float) basicScore) * dis * part * angle;
		return (int)floorf(score_);
	};

	void SetPlayerMat(Matrix mat) {
		playerrotation_ = mat;
	};

	void SetEnemyMat(Matrix mat) {
		enemyRotation_ = mat;
	};

private:
	int score_{ 0.0f };
	float dis{ 0.0f };
	float part{ 0.0f };
	float angle{ 0.0f };
	Vector2 distance{ Vector2::Vector2(30.0f, 50.0f) };
	Matrix playerrotation_{Matrix::Identity};
	Matrix enemyRotation_{Matrix::Identity};
};