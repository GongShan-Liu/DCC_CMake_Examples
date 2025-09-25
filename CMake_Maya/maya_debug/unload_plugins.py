#!/usr/bin/env python
# coding=utf-8

import os
import re
import socket
from pathlib import Path


def find_cmake_lists(root_dir):
    cmake_files = []
    for root, dirs, files in os.walk(root_dir):
        if "CMakeLists.txt" in files:
            cmake_files.append(os.path.join(root, "CMakeLists.txt").replace("\\", "/"))
    return cmake_files


def get_plugin_names():
    project_path = "%s/projects" % os.path.dirname(os.path.dirname(__file__)).replace(
        "\\", "/"
    )

    cmake_files = find_cmake_lists(project_path)

    results = []
    for f in cmake_files:
        text = Path(f).read_text(encoding="utf-8")
        match = re.search(r'project\s*\(\s*([^)]+)\s*\)', text, re.IGNORECASE)
        if match:
            results.append(match.group(1).strip())

    return results


plugin_names = get_plugin_names()


py_codes = """
#!/usr/bin/env python
# coding=utf-8

import traceback

import maya.cmds as cmds
import maya.api.OpenMaya as om

try:
    for p in %s:
        if cmds.pluginInfo(p, q=1, l=1):
            cmds.unloadPlugin(p)
            cmds.warning('unloadPlugin "' + p + '"')
except:
    om.MGlobal.displayError(traceback.format_exc())

""" % str(
    plugin_names
)


try:
    sk = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    sk.connect(("127.0.0.1", 7072))
    sk.send(py_codes.encode("utf-8"))
    sk.close()

except:
    print(u"连接失败maya端口: 7072.")
