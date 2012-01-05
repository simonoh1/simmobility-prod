#!/usr/bin/python

# Copyright Singapore-MIT Alliance for Research and Technology

from xml.etree import ElementTree

class Section:
    def __init__(self, id):
        self.id = id
        self.lane_edges = list()
        self.center_lines = list()

def output(road_network, network_name, file_name):
    sections = arrange(road_network)
    tree = build(sections, network_name)
    dump(tree, file_name)

def arrange(road_network):
    sections = dict()
    for lane_edge in road_network.lane_edges:
        if lane_edge.section_id not in sections:
            sections[lane_edge.section_id] = Section(lane_edge.section_id)
        section = sections[lane_edge.section_id]
        section.lane_edges.append(lane_edge)
    for center_line in road_network.lane_center_lines:
        if center_line.section_id not in sections:
            sections[center_line.section_id] = Section(center_line.section_id)
        section = sections[center_line.section_id]
        section.center_lines.append(center_line)

    for section in sections.values():
        section.lane_edges.sort(cmp=lane_edge_comparator)
        section.center_lines.sort(key=lambda line: line.index)

    return sections

def lane_edge_comparator(edge1, edge2):
    if edge1.type == edge2.type:
        return cmp(edge1.index, edge2.index)
    else:
        return cmp(edge1.type, edge2.type)

def build(sections, network_name):
    root = ElementTree.Element("road-network")
    root.set("name", network_name)
    comment = ElementTree.Comment("This file was generated by pqrne.  Do not edit.")
    root.append(comment)
    for section_id, section in sections.iteritems():
        section_element = ElementTree.SubElement(root, "section")
        section_element.set("section-id", str(section_id))
        edges_element = ElementTree.SubElement(section_element, "lane-edges")
        for edge in section.lane_edges:
            edge_element = ElementTree.SubElement(edges_element, "lane-edge")
            edge_element.set("type", edge.type)
            edge_element.set("index", str(edge.index))
            polyline_element = ElementTree.SubElement(edge_element, "polyline")
            for i, point in enumerate(edge.polyline):
                point_element = ElementTree.SubElement(polyline_element, "point")
                point_element.set("x", str(int(round(point.x))))
                point_element.set("y", str(int(round(point.y))))
                point_element.set("index", str(i))
        center_lines_element = ElementTree.SubElement(section_element, "center-lines")
        for line in section.center_lines:
            line_element = ElementTree.SubElement(center_lines_element, "center-line")
            line_element.set("type", line.type)
            line_element.set("index", str(line.index))
            attribute_element = ElementTree.SubElement(line_element, "lane-attributes")
            attribute_element.set("can-go-straight", value(line.can_go_straight))
            attribute_element.set("can-turn-left", value(line.can_turn_left))
            attribute_element.set("can-turn-right", value(line.can_turn_right))
            attribute_element.set("can-turn-on-red-signal", value(line.can_turn_on_red_signal))
            attribute_element.set("can-change-lane-left", value(line.can_change_lane_left))
            attribute_element.set("can-change-lane-right", value(line.can_change_lane_right))
            attribute_element.set("is-road-shoulder", value(line.is_road_shoulder))
            attribute_element.set("is-bicycle-lane", value(line.is_bicycle_lane))
            attribute_element.set("is-vehicle-lane", value(line.is_vehicle_lane))
            attribute_element.set("is-pedestrian-lane", value(line.is_pedestrian_lane))
            attribute_element.set("is-standard-bus-lane", value(line.is_standard_bus_lane))
            attribute_element.set("is-whole-day-bus-lane", value(line.is_whole_day_bus_lane))
            attribute_element.set("is-high-occupancy-vehicle-lane", value(line.is_high_occupancy_vehicle_lane))
            attribute_element.set("can-freely-park-here", value(line.can_freely_park_here))
            attribute_element.set("can-stop-here", value(line.can_stop_here))
            attribute_element.set("is-U-turn-allowed-here", value(line.is_U_turn_allowed_here))
            polyline_element = ElementTree.SubElement(line_element, "polyline")
            for i, point in enumerate(edge.polyline):
                point_element = ElementTree.SubElement(polyline_element, "point")
                point_element.set("x", str(int(round(point.x))))
                point_element.set("y", str(int(round(point.y))))
                point_element.set("index", str(i))
    indent(root)
    tree = ElementTree.ElementTree(root)
    return tree

def value(bool_value):
    return "true" if bool_value else "false"

# indent() was snarfed from http://effbot.org/zone/element-lib.htm#prettyprint
def indent(elem, level=0):
    i = '\n' + level * " "
    if len(elem):
        if not elem.text or not elem.text.strip():
            elem.text = i + " "
        if not elem.tail or not elem.tail.strip():
            elem.tail = i
        for elem in elem:
            indent(elem, level + 1)
        if not elem.tail or not elem.tail.strip():
            elem.tail = i
    else:
        if level and (not elem.tail or not elem.tail.strip()):
            elem.tail = i

def dump(tree, file_name):
    tree.write(file_name)
