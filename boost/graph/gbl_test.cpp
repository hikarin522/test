// gbl_test.cpp
// hikari

#include <fstream>
#include <iostream>
#include <string>
#include <cstdlib>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/graph/graphviz.hpp>

struct City {
    std::string name;
//    int population;
//    std::vector<int> zipcodes;
};

struct Highway {
    std::string name;
    double distance; // km
};

struct Country {
    std::string name;
};

typedef boost::adjacency_list<
    boost::listS, boost::vecS, boost::bidirectionalS,
    City,    // 頂点のBundleプロパティ
    Highway, // 辺のBundleプロパティ
    Country  // グラフのBundleプロパティ
> Map;

const char* NameList[] = {
    "Tokyo",
    "Nagoya",
    "Osaka",
    "Kobe",
    "Kanku"
};

int main()
{
    Map map;

    // グラフのBundleプロパティを設定
    map[boost::graph_bundle].name = "Japan";

    // 街(頂点)を2つ追加
    Map::vertex_descriptor v1 = add_vertex(map);
    Map::vertex_descriptor v2 = add_vertex(map);
    Map::vertex_descriptor v3 = add_vertex(map);
    Map::vertex_descriptor v4 = add_vertex(map);
    Map::vertex_descriptor v5 = add_vertex(map);

    // 頂点のBundleプロパティを設定
    map[v1].name = "Tokyo";
//    map[v1].population = 13221169;
//    map[v1].zipcodes.push_back(1500013);

    map[v2].name = "Nagoya";
//    map[v2].population = 2267048;
//    map[v2].zipcodes.push_back(4600006);

    map[v3].name = "Osaka";
    map[v4].name = "Kobe";
    map[v5].name = "Kanku";
//    map[v3].population = 1000000;
//    map[v3].zipcodes.push_back(5840082);

    // 辺を追加
    bool inserted = false;
    int dist;

    Map::edge_descriptor e;
    boost::tie(e, inserted) = add_edge(v1, v2, map);

    // 辺のBundleプロパティを設定
    std::cout << (map[e].name = "Tomei Expessway") << std::endl;
    std::cin >> dist;
    map[e].distance = dist;

    Map::edge_descriptor e2;
    boost::tie(e2, inserted) = add_edge(v2, v4, map);
    std::cout << (map[e2].name = "Meishin Expessway") << std::endl;
    std::cin >> dist;
    map[e2].distance = dist;

    Map::edge_descriptor e3;
    boost::tie(e3, inserted) = add_edge(v1, v5, map);
    std::cout << (map[e3].name = "Airplane") << std::endl;
    std::cin >> dist;
    map[e3].distance = dist;

    Map::edge_descriptor e4;
    boost::tie(e4, inserted) = add_edge(v4, v3, map);
    std::cout << (map[e4].name = "Hanshin Expessway") << std::endl;
    std::cin >> dist;
    map[e4].distance = dist;

    Map::edge_descriptor e5;
    boost::tie(e5, inserted) = add_edge(v5, v3, map);
    std::cout << (map[e5].name = "Kanku Expessway") << std::endl;
    std::cin >> dist;
    map[e5].distance = dist;

    // Highwayクラスのdistanceメンバを辺の重みとして計算
    std::vector<double> distance(boost::num_vertices(map));
    boost::dijkstra_shortest_paths(map, v1,
            boost::weight_map(boost::get(&Highway::distance, map)).
            distance_map(&distance[0]));

    std::cout << "Tokyo-Osaka : " << distance[v3] << "km" << std::endl;

    // graphvizの形式(*.dot)で出力
    std::ofstream file("test.dot");
    boost::write_graphviz(file, map, [=](std::ofstream &out, Map::edge_descriptor &i){return out << map[i].name;});//boost::make_label_writer(NameList));

    std::system("dot -Tpng test.dot -o test.png");

}
