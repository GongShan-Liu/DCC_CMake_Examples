#!/usr/bin/env python
# coding=utf-8


import os
import traceback

import maya.cmds as cmds
import maya.api.OpenMaya as om


if not cmds.commandPort(":7072", q=1):
    cmds.commandPort(n=":7072", stp="python")
    print("set command port=7072.")

try:
    execfile("%s/test_maya.py" % os.path.dirname(os.getcwd()).replace("\\", "/"))
except:
    om.MGlobal.displayError(traceback.format_exc())
