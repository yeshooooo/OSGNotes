//
// Created by yeshooo on 2024/5/20.
//

// 7-1 顶点访问器
#include <osgViewer/Viewer>
#include <osg/Node>
#include <osg/Geode>
#include <osg/Group>

#include <osgDB/ReadFile>
#include <osgDB/WriteFile>

#include <osgUtil/Optimizer>

#include <fstream>
#include <iostream>

// 顶点访问器,继承自osg::NodeVistor
class VertexVistor: public osg::NodeVisitor {
public:
    // 保存顶点数据
    osg::ref_ptr<osg::Vec3Array> extracted_verts;
public:
    // 构造函数,初始化并设置为遍历所有子节点
    VertexVistor(): osg::NodeVisitor(osg::NodeVisitor::TRAVERSE_ALL_CHILDREN) {
        extracted_verts = new osg::Vec3Array();
    }

    // 重载apply()方法
    void apply(osg::Geode& geode) {
        // 得到每一个drawable
        for(unsigned int i = 0; i < geode.getNumDrawables(); ++i) {
            // 得到几何体
            osg::Geometry* geom = dynamic_cast<osg::Geometry*>(geode.getDrawable(i));
            if (!geom) {
                std::cout << "集合体错误! \n";
                continue;
            }
            // 得到顶点数组
            osg::Vec3Array* verts = dynamic_cast<osg::Vec3Array*>(geom->getVertexArray());
            if (!verts)
            {
                std::cout << "顶点数组错误！\n";
                continue;
            }
            // 添加到extracted_verts
            extracted_verts->insert(extracted_verts->end(), verts->begin(),verts->end());

        }

    }


};

int main() {
    // 创建Viewer对象, 场景浏览器
    osg::ref_ptr<osgViewer::Viewer> viewer = new osgViewer::Viewer();

    osg::ref_ptr<osg::Group> root = new osg::Group();

    // 读取滑翔机模型
   osg::ref_ptr<osg::Node> node = osgDB::readNodeFile("glider.osg");
   root->addChild(node.get());

   // 创建顶点访问器对象
   VertexVistor vtea;

   // 开始执行访问器遍历
   node->accept(vtea);

   // 申请一个输出流
   std::ofstream fout("glider.vertexs");

   // 得到顶点数组的大小
   int size_t = vtea.extracted_verts->size();

   // 初始化一个迭代器
   std::vector<osg::Vec3> ::iterator iter = vtea.extracted_verts->begin();

   // 写入文件
    for (int i = 0; i < size_t; ++i) {
        fout << iter->x() << "  " << iter->y() << "  " << iter->z() << std::endl;
        iter++;
    }

    // 优化场景数据
    osgUtil::Optimizer optimizer;
    optimizer.optimize(root.get());

    viewer->setSceneData(root.get());

    viewer->realize();
    viewer->run();
    return 0;
}