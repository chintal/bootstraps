#!/usr/bin/python

import pydotplus

import sys

hidden_nodes = [{'label': 'uc_types.h',
                 'name': '',
                 'exceptions': ['stdint.h', 'uc_pum.h', 'uc_pum_lp5529.h'],
                 'color': 'aquamarine'},
                {'label': 'uc_pum.h',
                 'name': '',
                 'exceptions': ['uc_pum_lp5529.h'],
                 'color': 'aquamarine4'},
                {'label': 'board_pum.h',
                 'name': '',
                 'exceptions': ['board_pum_lp5529.h'],
                 'color': 'darkolivegreen3'},
                {'label': 'stdint.h',
                 'name': '',
                 'exceptions': ['uc_types.h'],
                 'color': 'blue'},
                {'label': 'inc/hw_memmap.h',
                 'name': '',
                 'exceptions': ['msp430.h','msp430f5xx_6xxgeneric.h', 'stdint.h', 'stdbool.h'],
                 'color': 'lightpink'}]


def find_node_name(hlabel, nodes):
    for node in nodes:
        if node.get_label() == "\"" + hlabel + "\"":
            return node.get_name()


def replace_last(source_string, replace_what, replace_with):
    head, sep, tail = source_string.rpartition(replace_what)
    return head + replace_with + tail


def get_new_source_label(node, color):
    if node.get_label().startswith('<'):
        return replace_last(node.get_label(), "<TR>", "<TR><TD BGCOLOR=\"" + color + "\" WIDTH=\"5\"></TD>")
    return "<<TABLE CELLSPACING=\"0\" CELLBORDER=\"0\" BORDER=\"0\"><TR><TD BGCOLOR=\"" + color + \
           "\" WIDTH=\"5\"></TD><TD>" + node.get_label().strip('"') + \
           "</TD></TR></TABLE>>"


def get_new_dest_label(node, color):
    if node.get_label().startswith('<'):
        return replace_last(node.get_label(), "</TR>", "<TD BGCOLOR=\"" + color + "\" WIDTH=\"5\"></TD></TR>")
    return "<<TABLE CELLSPACING=\"0\" CELLBORDER=\"0\" BORDER=\"0\"><TR><TD>" + node.get_label().strip('"') + \
           "</TD><TD BGCOLOR=\"" + color + \
           "\" WIDTH=\"5\"></TD></TR></TABLE>>"


def simplify(fname):
    dfile = pydotplus.graph_from_dot_file(fname)
    nodes = dfile.get_nodes()
    dfile.write_png('main_original.png', prog='dot')
    for hnode in hidden_nodes:
        hnode['name'] = find_node_name(hnode['label'], nodes)
    hnodenames = [hnode['name'] for hnode in hidden_nodes]
    for hnode in hidden_nodes:
        color = hnode['color']
        enodenames = []
        for enodename in hnode['exceptions']:
            enodenames.append(find_node_name(enodename, nodes))
        edges = dfile.get_edges()
        for edge in edges:
            if edge.get_destination() == hnode['name']:
                if edge.get_source() in enodenames:
                    pass
                elif edge.get_source() in hnodenames:
                    pass
                else:
                    for node in nodes:
                        if node.get_name() == edge.get_source():
                            node.set_label(get_new_source_label(node, color))
                    dfile.del_edge(edge.get_source(), edge.get_destination())

            if edge.get_source() == hnode['name']:
                if edge.get_destination() in enodenames:
                    pass
                elif edge.get_destination() in hnodenames:
                    pass
                else:
                    for node in nodes:
                        if node.get_name() == edge.get_source():
                            node.set_label(get_new_dest_label(node, color))
                    dfile.del_edge(edge.get_source(), edge.get_destination())

        for node in nodes:
            if node.get_name() == hnode['name']:
                    node.set_label(get_new_dest_label(node, color))

    dfile.write(fname, prog='dot')


if __name__ == "__main__":
    simplify(sys.argv[1])
