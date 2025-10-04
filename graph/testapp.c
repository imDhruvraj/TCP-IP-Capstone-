#include "graph.h"

int main() {
    graph_t *topo = create_new_graph("Topology-1");

    node_t *R0 = create_graph_node(topo, "R0");
    node_t *R1 = create_graph_node(topo, "R1");
    node_t *R2 = create_graph_node(topo, "R2");

    insert_link_between_two_nodes(R0, R1, "eth0/0", "eth0/1", 1);
    insert_link_between_two_nodes(R1, R2, "eth0/2", "eth0/3", 1);
    insert_link_between_two_nodes(R0, R2, "eth0/4", "eth0/5", 1);

    dump_graph(topo);

    return 0;
}
