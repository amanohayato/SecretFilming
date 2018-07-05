#pragma once
#include<vector>
#include<queue>
#include<functional>
#include<limits>
#include"../Math/Vector3.h"
#include"WalkGraph.h"

class WalkPath {
	using f_g = std::pair<float, float>;//�\�z����,����
	using dist_node = std::pair<f_g, int>;//�����ƃm�[�h�ԍ��̃y�A(�����Ǝ��g�̐e�m�[�h�̔ԍ�)

public:
	static std::vector<int> find_path(const WalkGraph& graph,int sheet, int start, int end) {
		const auto inf = FLT_MAX;//float�̍ő�l
		std::vector<dist_node> dist_nodes(graph.node_count(sheet), { { inf,inf },-1 });//�o�H���(�������̕��ɂ͍ő�l�����Ă���)
		std::priority_queue<dist_node, std::vector<dist_node>, std::greater<dist_node>> queue;//���v�R�X�g�̏��Ȃ��o�H���擾���邽�߂�priority_queue,�D��x���r���ŕς�������ɑg�ݒ����Ȃ����߁A�ŒZ���X�V���Ȃ��Ă��ǂ��悤�ɉ��ł͂�����������Ȃ��͖̂�������悤�ɂ��Ă���
		dist_nodes[start] = { { 0.0f,0.0f },-1 };//�J�n�m�[�h���L���[�ɓo�^
		queue.push({ { 0.0f,0.0f },start });

		while (!queue.empty())//�L���[�Ƀf�[�^���c���Ă����
		{
			const auto front = queue.top(); queue.pop();//�擪�m�[�h���L���[������o��
			const auto front_f_g = front.first;//���v����
			const auto front_node = front.second;//�m�[�h�ԍ�

			if (front_node == end) {//�S�[���ɂ�����
				return create_path(dist_nodes, end);//�����p�X���쐬����
			}
			/*
			�L���[���̃f�[�^�����o�H���̍��v������������������A(�L���[���̃f�[�^�������Â�������)
			�L���[���̃f�[�^�͍ŒZ�����ł͂Ȃ����ߖ���
			*/
			if (dist_nodes[front_node].first < front_f_g)continue;

			for (const auto& edge : graph.getNode(sheet,front_node).edges) {//���Ӄm�[�h���擾(���g���ړ��\�ȋߗ׃m�[�h���擾)
				const auto g = dist_nodes[front_node].first.second + edge.cost;//���v���������߂�(�ړ��R�X�g�͈ꗥ1.0f�Ƃ���
				if (dist_nodes[edge.node].first.second > g) {//���v��������������΍ŒZ�����Ƃ��ăL���[�ɓo�^
					const auto h = Vector3::Distance(graph.getNode(sheet,edge.node).position,graph.getNode(sheet, end).position);//�S�[���܂ł̋���
					const auto f = g + h;//�\�z����
					dist_nodes[edge.node] = { { f,g },front_node };//�e�̌o�H����ۑ�
					queue.push({ { f,g },edge.node });//�ړ��R�X�g�̍��v�Ƌߗ׃m�[�h���L���[�ɒǉ�(push���_�ŏ���ɕ��בւ��Ă����)
				}
			}
		}
		return std::vector<int>();//�o�H��������Ȃ��Ȃ��p�X��Ԃ�
	}

private:
	//�S�[������X�^�[�g�֌������p�X�����o��
	static std::vector<int> create_path(const std::vector<dist_node>& dist_nodes, int end) {
		std::vector<int> path;
		for (int node = end; node != -1; node = dist_nodes[node].second) {//�X�^�[�g�n�_�͐e�m�[�h�ԍ���-1�Ƃ��Ď����Ă��邽�߁A����ɓ��B����܂ŉ�(��̕���-1�����Ă�)
			path.push_back(node);
		}
		return path;
	}
};

