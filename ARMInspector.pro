TEMPLATE = subdirs
SUBDIRS = ARMInspectorGUI ARMInspectorServer

ARMInspectorGUI.subdir = ARMInspectorGUI
ARMInspectorServer.subdir = ARMInspectorServer
ARMInspectorGUI.depends = ARMInspectorServer

!defined(BRAND, var)
{
    BRAND = ARMInspector
}
