// dot_test.cpp
// hikari

#include <fstream>
#include <vector>
#include <string>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graphviz.hpp>

typedef
    boost::adjacency_list<boost::listS, boost::vecS, boost::directedS,
        boost::no_property, boost::property<boost::edge_weight_t, int>>
Graph;

typedef std::pair<int, int> Edge;

enum { A, B, C, D, E, N };
const std::string name = "ABCDEFGHIJKLMN";

const char* NameList[] = {
    "Yokohama",
    "MusashiKosugi",
    "Kawasaki",
    "Shibuya",
    "Tokyo"
};

template <class Graph>
struct weight_label_writer {
    weight_label_writer(const Graph& g) : graph_(g) {}

    template <class Edge>
    void operator()(std::ostream& out, const Edge& edge) const
    {
        write(out, edge, boost::get(boost::edge_weight, graph_, edge));
    }

private:
    template <class Edge, class Weight>
    void write(std::ostream& out, const Edge& edge, const Weight& weight) const
    {
        out << "[weight="
            << weight
            << ", label="
            << weight
            << "]";
    }

    const Graph& graph_;
};

template <class Graph>
inline weight_label_writer<Graph> make_weight_label_writer(const Graph& g)
{
    return weight_label_writer<Graph>(g);
}

int main()
{
    const std::vector<Edge> edges = {
        {A, B}, {A, C}, {A, D},
        {B, E}, {C, E}, {D, E}
    };

    const std::vector<int> weights = {
        3, 1, 4,
        5, 2, 6
    };

    const Graph g(edges.begin(), edges.end(), weights.begin(), N);

    std::ofstream file("test.dot");
    boost::write_graphviz(file, g,
            boost::make_label_writer(NameList),
            make_weight_label_writer(g));

    std::system("dot -Tpng test.dot -o test.png");
}
