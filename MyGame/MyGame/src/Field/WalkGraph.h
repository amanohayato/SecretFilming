#pragma once
#include<vector>
#include<string>
#include"../Math/Vector3.h"
#include<vector>
#include<queue>
#include<functional>
#include<list>

class WalkGraph {
	using f_g = std::pair<float, float>;//予想距離,距離
	using dist_node = std::pair<f_g, int>;//距離とノード番号のペア(距離と自身の親ノードの番号)
public:
	struct Edge {
		int node;//接続先ノード番号
		float cost;//移動コスト
	};
	struct Node {
		Vector3 position;
		std::vector<Edge> edges;//エッジ
	};
	WalkGraph() = default;

	void initialize();
	void load(const std::string& pointfilename, const std::string& pathfilename);
	//ノードを取得
	const Node& getNode(int sheet, int index)const;
	//ノード数を取得
	std::size_t node_count(int sheet)const;
	//最近ノードのキーを取得
	int getNearestNode(int sheet, const Vector3& position)const;

	int clearEdge(int sheet, const Vector3& position, int width, int height);
	void createEdge(int sheet, int indexNum);

	const std::vector<Node>& getNode(int sheet)const {
		return nodes_[sheet];
	}
	//現在座標から、目的座標に最も近いポイントへ向かうルートを取得する
	std::vector<Vector3> find_path(int sheet, const Vector3& current, const Vector3& target) {
		int currentNode = getNearestNode(sheet, current);
		int targetNode = getNearestNode(sheet, target);

		return find_path(sheet, currentNode, targetNode);
	}

private:
	std::vector<Vector3> find_path(int sheet, int start, int end) {
		const auto inf = FLT_MAX;//floatの最大値
		std::vector<dist_node> dist_nodes(node_count(sheet), { { inf,inf },-1 });//経路情報(未検索の物には最大値を入れておく)
		std::priority_queue<dist_node, std::vector<dist_node>, std::greater<dist_node>> queue;//合計コストの少ない経路を取得するためのpriority_queue,優先度が途中で変わった時に組み直せないため、最短を更新しなくても良いように下ではそもそもいらないのは無視するようにしている
		dist_nodes[start] = { { 0.0f,0.0f },-1 };//開始ノードをキューに登録
		queue.push({ { 0.0f,0.0f },start });

		while (!queue.empty())//キューにデータが残ってる限り
		{
			const auto front = queue.top(); queue.pop();//先頭ノードをキューから取り出す
			const auto front_f_g = front.first;//合計距離
			const auto front_node = front.second;//ノード番号

			if (front_node == end) {//ゴールについたら
				return create_path(sheet,dist_nodes, end);//検索パスを作成する
			}
			/*
			キュー内のデータよりも経路情報の合計距離が小さかったら、(キュー内のデータがもう古かったら)
			キュー内のデータは最短距離ではないため無視
			*/
			if (dist_nodes[front_node].first < front_f_g)continue;

			for (const auto& edge : getNode(sheet, front_node).edges) {//周辺ノードを取得(自身が移動可能な近隣ノードを取得)
				const auto g = dist_nodes[front_node].first.second + edge.cost;//合計距離を求める(移動コストは一律1.0fとする
				if (dist_nodes[edge.node].first.second > g) {//合計距離が小さければ最短距離としてキューに登録
					const auto h = Vector3::Distance(getNode(sheet, edge.node).position, getNode(sheet, end).position);//ゴールまでの距離
					const auto f = g + h;//予想距離
					dist_nodes[edge.node] = { { f,g },front_node };//親の経路情報を保存
					queue.push({ { f,g },edge.node });//移動コストの合計と近隣ノードをキューに追加(push時点で勝手に並べ替えてくれる)
				}
			}
		}
		return std::vector<Vector3>();//経路が見つからないなら空パスを返す
	}

	//ゴールからスタートへ向かうパスを作り出す
	std::vector<Vector3> create_path(int sheet,const std::vector<dist_node>& dist_nodes, int end) {
		std::vector<Vector3> path;
		for (int node = end; node != -1; node = dist_nodes[node].second) {//スタート地点は親ノード番号を-1として持っているため、それに到達するまで回す(上の方で-1を入れてる)
			path.push_back(nodes_.at(sheet).at(node).position);
		}
		return path;
	}

private:
	int currentSheet_{ 0 };
	std::vector<std::vector<Node>> nodes_;
	int indexNum_{ 0 };
	std::vector<std::list<std::tuple<int, int,float>>> node_edge_connect_list_;//対象ノード番号,削除エッジ番号,コスト

};
