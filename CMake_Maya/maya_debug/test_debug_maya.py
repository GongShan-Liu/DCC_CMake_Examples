#!/usr/bin/env python
# coding=utf-8

import os
import socket

project_path = os.path.dirname(os.path.dirname(__file__)).replace("\\", "/")
py_file = "%s/test_maya.py" % project_path

py_codes = (
    """
#!/usr/bin/env python
# coding=utf-8

import traceback

import maya.cmds as cmds
import maya.api.OpenMaya as om

try:
    execfile(\"%s\")
except:
    om.MGlobal.displayError(traceback.format_exc())
"""
    % py_file
)

try:
    sk = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    sk.connect(("127.0.0.1", 7072))
    sk.send(py_codes.encode("utf-8"))
    sk.close()

except:
    print(u"连接失败maya端口: 7072.")
