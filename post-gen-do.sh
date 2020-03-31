diff --git a/kubernetes/CMakeLists.txt b/kubernetes/CMakeLists.txt
index 437833a..96b7c98 100644
--- a/kubernetes/CMakeLists.txt
+++ b/kubernetes/CMakeLists.txt
@@ -9,6 +9,7 @@ set(CMAKE_VISIBILITY_INLINES_HIDDEN OFF)
 set(CMAKE_BUILD_TYPE Debug)

 set(pkgName "kubernetes")
+ADD_DEFINITIONS(-DOPENSSL)

 find_package(CURL 7.58.0 REQUIRED)
 if(CURL_FOUND)
@@ -18,9 +19,10 @@ else(CURL_FOUND)
        message(FATAL_ERROR "Could not find the CURL library and development files.")
 endif()

+
 set(SRCS
     config/kube_config_yaml.c
-#config/kube_config.c
+    config/kube_config.c
     src/list.c
     src/apiKey.c
     src/apiClient.c
@@ -774,6 +776,7 @@ set(SRCS
 set(HDRS
     config/kube_config_model.h
     config/kube_config_yaml.h
+    config/kube_config.h
     include/apiClient.h
     include/list.h
     include/keyValuePair.h


and

data write call back function

