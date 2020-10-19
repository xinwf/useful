#include <iostream>
#include <vector>
#include <deque>
#include <queue>

typedef struct _BiNode{
    int data;
    struct _BiNode * left;
    struct _BiNode * right;
} BiNode, *PBiNode;

class BiTree{
    PBiNode m_root;
    std::queue<PBiNode> m_biNode_que;
public:
    BiTree();
    void createTree(const std::vector<int> & vec, int & count, PBiNode node);
    PBiNode getRoot();
    void preOutput(PBiNode node);
    void midOutput(PBiNode node);
    void aftOutput(PBiNode node);
    void layerOutput(PBiNode node);
};

BiTree::BiTree(){
    m_root = nullptr;
}

void BiTree::createTree(const std::vector<int> & vec, int & count, PBiNode node = nullptr){
    if((count > vec.size() - 1)){
        std::queue<PBiNode> empty_biNode_que;
        std::swap(empty_biNode_que, m_biNode_que);
        std::cout << "Create finish.\n";
        return;
    }

    // std::cout << "node's addr: " << node << "\n";

    if(m_root == nullptr){
        m_root = new BiNode;
        m_biNode_que.push(m_root);
        // std::cout << "m_root: " << m_root << "\n";
        // std::cout << "Create node with: " << vec[count] << " for root.\n";
        m_root->data = vec[count];
        m_root->left = nullptr;
        m_root->right = nullptr;
        ++count;
        // std::cout << "m_root->left: " << m_root->left << "\n";
        // std::cout << "m_root->right: " << m_root->right << "\n";
        // m_biNode_que.push(m_root->left);
        // m_biNode_que.push(m_root->right);
        createTree(vec, count, m_biNode_que.front());
    }else{
        PBiNode tmp = new BiNode;
        // PBiNode tmp = m_biNode_que.front();
        // tmp = new BiNode;
        // std::cout << "Create node with: " << vec[count] << "\n";
        tmp->data = vec[count];
        tmp->left = nullptr;
        tmp->right = nullptr;
        // std::cout << "tmp: " << tmp << "\n";
        // std::cout << "tmp->left: " << tmp->left << "\n";
        // std::cout << "tmp->right: " << tmp->right << "\n";
        // std::cout << "m_biNode_que size: " << m_biNode_que.size() << "\n";
        ++count;
        m_biNode_que.push(tmp);
        // std::cout << "m_biNode_que size: " << m_biNode_que.size() << "\n";
        if(node->left == nullptr){
            // std::cout << "Let node->left equal to tmp.\n";
            node->left = tmp;
        }
        else{
            // std::cout << "Let node->right equal to tmp. m_biNode_que size: " << m_biNode_que.size() << "\n";
            node->right = tmp;
            m_biNode_que.pop();
        }
        createTree(vec, count, m_biNode_que.front());
    }
}

PBiNode BiTree::getRoot(){
    // std::cout << "m_root: " << m_root << "\n";
    // std::cout << "m_root->left: " << m_root->left << "\n";
    // std::cout << "m_root->right: " << m_root->right << "\n";
    if(m_root == nullptr) std::cout << "Root is null.\n";
    // std::cout << "Root data: " << m_root->data << "\n";
    return m_root;
}

void BiTree::preOutput(PBiNode node){
    if(node == nullptr){
        // std::cout << "Node is null.\n";
        // std::cout << "\n";
        return;
    }
    std::cout << node->data << " ";
    preOutput(node->left);
    preOutput(node->right);
}

void BiTree::midOutput(PBiNode node){
    if(node == nullptr){
        // std::cout << "Node is null.\n";
        // std::cout << "\n";
        return;
    }
    midOutput(node->left);
    std::cout << node->data << " ";
    midOutput(node->right);
}
void BiTree::aftOutput(PBiNode node){
    if(node == nullptr){
        // std::cout << "Node is null.\n";
        // std::cout << "\n";
        return;
    }
    aftOutput(node->left);
    aftOutput(node->right);
    std::cout << node->data << " ";
}

void BiTree::layerOutput(PBiNode node){
    if(node == nullptr){
        return;
    }
    if(m_biNode_que.size() != 0 ){
        m_biNode_que.pop();
    }
    std::cout << node->data << " ";
    m_biNode_que.push(node->left);
    m_biNode_que.push(node->right);
    layerOutput(m_biNode_que.front());
}

int main()
{
    std::vector<int> intV = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    int count = 0;
    BiTree biTree;
    biTree.createTree(intV, count);
    std::cout << "Pre output: ";
    biTree.preOutput(biTree.getRoot());
    std::cout << "\n";
    std::cout << "Mid output: ";
    biTree.midOutput(biTree.getRoot());
    std::cout << "\n";
    std::cout << "Aft output: ";
    biTree.aftOutput(biTree.getRoot());
    std::cout << "\n";
    std::cout << "Layer output: ";
    biTree.layerOutput(biTree.getRoot());
    std::cout << "\n";
    return 0;
}