#pragma once
#include<vector>
#include<string>
#include"../Math/Vector3.h"
#include<vector>
#include<queue>
#include<functional>
#include<list>

class WalkGraph {
	using f_g = std::pair<float, float>;//�\�z����,����
	using dist_node = std::pair<f_g, int>;//�����ƃm�[�h�ԍ��̃y�A(�����Ǝ��g�̐e�m�[�h�̔ԍ�)
public:
	struct Edge {
		int node;//�ڑ���m�[�h�ԍ�
		float cost;//�ړ��R�X�g
	};
	struct Node {
		Vector3 position;
		std::vector<Edge> edges;//�G�b�W
	};
	WalkGraph() = default;

	void initialize();
	void load(const std::string& pointfilename, const std::string& pathfilename);
	//�m�[�h���擾
	const Node& getNode(int sheet, int index)const;
	//�m�[�h�����擾
	std::size_t node_count(int sheet)const;
	//�ŋ߃m�[�h�̃L�[���擾
	int getNearestNode(int sheet, const Vector3& position)const;

	int clearEdge(int sheet, const Vector3& position, int width, int height);
	void createEdge(int sheet, int indexNum);

	const std::vector<Node>& getNode(int sheet)const {
		return nodes_[sheet];
	}
	//���ݍ��W����A�ړI���W�ɍł��߂��|�C���g�֌��������[�g���擾����
	std::vector<Vector3> find_path(int sheet, const Vector3& current, const Vector3& target) {
		int currentNode = getNearestNode(sheet, current);
		int targetNode = getNearestNode(sheet, target);

		return find_path(sheet, currentNode, targetNode);
	}

private:
	std::vector<Vector3> find_path(int sheet, int start, int end) {
		const auto inf = FLT_MAX;//float�̍ő�l
		std::vector<dist_node> dist_nodes(node_count(sheet), { { inf,inf },-1 });//�o�H���(�������̕��ɂ͍ő�l�����Ă���)
		std::priority_queue<dist_node, std::vector<dist_node>, std::greater<dist_node>> queue;//���v�R�X�g�̏��Ȃ��o�H���擾���邽�߂�priority_queue,�D��x���r���ŕς�������ɑg�ݒ����Ȃ����߁A�ŒZ���X�V���Ȃ��Ă��ǂ��悤�ɉ��ł͂�����������Ȃ��͖̂�������悤�ɂ��Ă���
		dist_nodes[start] = { { 0.0f,0.0f },-1 };//�J�n�m�[�h���L���[�ɓo�^
		queue.push({ { 0.0f,0.0f },start });

		while (!queue.empty())//�L���[�Ƀf�[�^���c���Ă����
		{
			const auto front = queue.top(); queue.pop();//�擪�m�[�h���L���[������o��
			const auto front_f_g = front.first;//���v����
			const auto front_node = front.second;//�m�[�h�ԍ�

			if (front_node == end) {//�S�[���ɂ�����
				return create_path(sheet,dist_nodes, end);//�����p�X���쐬����
			}
			/*
			�L���[���̃f�[�^�����o�H���̍��v������������������A(�L���[���̃f�[�^�������Â�������)
			�L���[���̃f�[�^�͍ŒZ�����ł͂Ȃ����ߖ���
			*/
			if (dist_nodes[front_node].first < front_f_g)continue;

			for (const auto& edge : getNode(sheet, front_node).edges) {//���Ӄm�[�h���擾(���g���ړ��\�ȋߗ׃m�[�h���擾)
				const auto g = dist_nodes[front_node].first.second + edge.cost;//���v���������߂�(�ړ��R�X�g�͈ꗥ1.0f�Ƃ���
				if (dist_nodes[edge.node].first.second > g) {//���v��������������΍ŒZ�����Ƃ��ăL���[�ɓo�^
					const auto h = Vector3::Distance(getNode(sheet, edge.node).position, getNode(sheet, end).position);//�S�[���܂ł̋���
					const auto f = g + h;//�\�z����
					dist_nodes[edge.node] = { { f,g },front_node };//�e�̌o�H����ۑ�
					queue.push({ { f,g },edge.node });//�ړ��R�X�g�̍��v�Ƌߗ׃m�[�h���L���[�ɒǉ�(push���_�ŏ���ɕ��בւ��Ă����)
				}
			}
		}
		return std::vector<Vector3>();//�o�H��������Ȃ��Ȃ��p�X��Ԃ�
	}

	//�S�[������X�^�[�g�֌������p�X�����o��
	std::vector<Vector3> create_path(int sheet,const std::vector<dist_node>& dist_nodes, int end) {
		std::vector<Vector3> path;
		for (int node = end; node != -1; node = dist_nodes[node].second) {//�X�^�[�g�n�_�͐e�m�[�h�ԍ���-1�Ƃ��Ď����Ă��邽�߁A����ɓ��B����܂ŉ�(��̕���-1�����Ă�)
			path.push_back(nodes_.at(sheet).at(node).position);
		}
		return path;
	}

private:
	int currentSheet_{ 0 };
	std::vector<std::vector<Node>> nodes_;
	int indexNum_{ 0 };
	std::vector<std::list<std::tuple<int, int,float>>> node_edge_connect_list_;//�Ώۃm�[�h�ԍ�,�폜�G�b�W�ԍ�,�R�X�g

};
