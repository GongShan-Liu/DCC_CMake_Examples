#!/usr/bin/env python
# coding=utf-8

import maya.cmds as cmds

# help(cmds)
print(u"hello world 你好")

if not cmds.pluginInfo("testCommandPlugin", q=1, l=1):
    cmds.loadPlugin("testCommandPlugin")

cmds.runTest()
