#pragma once
#include"ActorPtr.h"
#include<map>
#include<list>

enum class ActorGroup;
enum class EventMessage;
class ActorManager {
public:
	ActorManager();

	// 初期化
	void initialize();
	// 更新
	void update(float deltaTime);
	// 描画
	void draw() const;
	void shadowDraw()const;
	void remove();
	// アクターの追加
	void addActor(ActorGroup group, const ActorPtr& actor);
	// アクターの検索
	ActorPtr findActor(const std::string& name);
	// アクターの一括検索
	void findActor(ActorGroup group,const std::string& name, std::list<std::weak_ptr<Actor>>& actorList);
	// メッセージ処理
	void handleMessage(EventMessage message, void* param);

	unsigned int getSize(ActorGroup group) const;

	// コピー禁止
	ActorManager(const ActorManager& other) = delete;
	ActorManager& operator = (const ActorManager& other) = delete;

	// 衝突判定
	void collide();

	std::map<ActorGroup, ActorPtr>& get();

private:
	//キャラクターに識別番号を設定する
	int countList_{ 0 };
private:
	//アクター一覧
	std::map<ActorGroup,ActorPtr> actors_;

	ActorPtr root_{ nullptr };
};