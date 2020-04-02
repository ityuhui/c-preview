#include <stdlib.h>
#include <stdio.h>
#include "../include/apiClient.h"
#include "../include/list.h"
#include "../external/cJSON.h"
#include "../include/keyValuePair.h"
#include "../model/v1_api_resource_list.h"
#include "../model/v1_delete_options.h"
#include "../model/v1_status.h"
#include "../model/v1beta1_csi_driver.h"
#include "../model/v1beta1_csi_driver_list.h"
#include "../model/v1beta1_csi_node.h"
#include "../model/v1beta1_csi_node_list.h"
#include "../model/v1beta1_storage_class.h"
#include "../model/v1beta1_storage_class_list.h"
#include "../model/v1beta1_volume_attachment.h"
#include "../model/v1beta1_volume_attachment_list.h"


// create a CSIDriver
//
v1beta1_csi_driver_t*
StorageV1beta1API_createCSIDriver(apiClient_t *apiClient, v1beta1_csi_driver_t * body , char * pretty , char * dryRun , char * fieldManager );


// create a CSINode
//
v1beta1_csi_node_t*
StorageV1beta1API_createCSINode(apiClient_t *apiClient, v1beta1_csi_node_t * body , char * pretty , char * dryRun , char * fieldManager );


// create a StorageClass
//
v1beta1_storage_class_t*
StorageV1beta1API_createStorageClass(apiClient_t *apiClient, v1beta1_storage_class_t * body , char * pretty , char * dryRun , char * fieldManager );


// create a VolumeAttachment
//
v1beta1_volume_attachment_t*
StorageV1beta1API_createVolumeAttachment(apiClient_t *apiClient, v1beta1_volume_attachment_t * body , char * pretty , char * dryRun , char * fieldManager );


// delete a CSIDriver
//
v1_status_t*
StorageV1beta1API_deleteCSIDriver(apiClient_t *apiClient, char * name , char * pretty , char * dryRun , int gracePeriodSeconds , int orphanDependents , char * propagationPolicy , v1_delete_options_t * body );


// delete a CSINode
//
v1_status_t*
StorageV1beta1API_deleteCSINode(apiClient_t *apiClient, char * name , char * pretty , char * dryRun , int gracePeriodSeconds , int orphanDependents , char * propagationPolicy , v1_delete_options_t * body );


// delete collection of CSIDriver
//
v1_status_t*
StorageV1beta1API_deleteCollectionCSIDriver(apiClient_t *apiClient, char * pretty , int allowWatchBookmarks , char * _continue , char * dryRun , char * fieldSelector , int gracePeriodSeconds , char * labelSelector , int limit , int orphanDependents , char * propagationPolicy , char * resourceVersion , int timeoutSeconds , int watch , v1_delete_options_t * body );


// delete collection of CSINode
//
v1_status_t*
StorageV1beta1API_deleteCollectionCSINode(apiClient_t *apiClient, char * pretty , int allowWatchBookmarks , char * _continue , char * dryRun , char * fieldSelector , int gracePeriodSeconds , char * labelSelector , int limit , int orphanDependents , char * propagationPolicy , char * resourceVersion , int timeoutSeconds , int watch , v1_delete_options_t * body );


// delete collection of StorageClass
//
v1_status_t*
StorageV1beta1API_deleteCollectionStorageClass(apiClient_t *apiClient, char * pretty , int allowWatchBookmarks , char * _continue , char * dryRun , char * fieldSelector , int gracePeriodSeconds , char * labelSelector , int limit , int orphanDependents , char * propagationPolicy , char * resourceVersion , int timeoutSeconds , int watch , v1_delete_options_t * body );


// delete collection of VolumeAttachment
//
v1_status_t*
StorageV1beta1API_deleteCollectionVolumeAttachment(apiClient_t *apiClient, char * pretty , int allowWatchBookmarks , char * _continue , char * dryRun , char * fieldSelector , int gracePeriodSeconds , char * labelSelector , int limit , int orphanDependents , char * propagationPolicy , char * resourceVersion , int timeoutSeconds , int watch , v1_delete_options_t * body );


// delete a StorageClass
//
v1_status_t*
StorageV1beta1API_deleteStorageClass(apiClient_t *apiClient, char * name , char * pretty , char * dryRun , int gracePeriodSeconds , int orphanDependents , char * propagationPolicy , v1_delete_options_t * body );


// delete a VolumeAttachment
//
v1_status_t*
StorageV1beta1API_deleteVolumeAttachment(apiClient_t *apiClient, char * name , char * pretty , char * dryRun , int gracePeriodSeconds , int orphanDependents , char * propagationPolicy , v1_delete_options_t * body );


// get available resources
//
v1_api_resource_list_t*
StorageV1beta1API_getAPIResources(apiClient_t *apiClient);


// list or watch objects of kind CSIDriver
//
v1beta1_csi_driver_list_t*
StorageV1beta1API_listCSIDriver(apiClient_t *apiClient, char * pretty , int allowWatchBookmarks , char * _continue , char * fieldSelector , char * labelSelector , int limit , char * resourceVersion , int timeoutSeconds , int watch );


// list or watch objects of kind CSINode
//
v1beta1_csi_node_list_t*
StorageV1beta1API_listCSINode(apiClient_t *apiClient, char * pretty , int allowWatchBookmarks , char * _continue , char * fieldSelector , char * labelSelector , int limit , char * resourceVersion , int timeoutSeconds , int watch );


// list or watch objects of kind StorageClass
//
v1beta1_storage_class_list_t*
StorageV1beta1API_listStorageClass(apiClient_t *apiClient, char * pretty , int allowWatchBookmarks , char * _continue , char * fieldSelector , char * labelSelector , int limit , char * resourceVersion , int timeoutSeconds , int watch );


// list or watch objects of kind VolumeAttachment
//
v1beta1_volume_attachment_list_t*
StorageV1beta1API_listVolumeAttachment(apiClient_t *apiClient, char * pretty , int allowWatchBookmarks , char * _continue , char * fieldSelector , char * labelSelector , int limit , char * resourceVersion , int timeoutSeconds , int watch );


// partially update the specified CSIDriver
//
v1beta1_csi_driver_t*
StorageV1beta1API_patchCSIDriver(apiClient_t *apiClient, char * name , object_t * body , char * pretty , char * dryRun , char * fieldManager , int force );


// partially update the specified CSINode
//
v1beta1_csi_node_t*
StorageV1beta1API_patchCSINode(apiClient_t *apiClient, char * name , object_t * body , char * pretty , char * dryRun , char * fieldManager , int force );


// partially update the specified StorageClass
//
v1beta1_storage_class_t*
StorageV1beta1API_patchStorageClass(apiClient_t *apiClient, char * name , object_t * body , char * pretty , char * dryRun , char * fieldManager , int force );


// partially update the specified VolumeAttachment
//
v1beta1_volume_attachment_t*
StorageV1beta1API_patchVolumeAttachment(apiClient_t *apiClient, char * name , object_t * body , char * pretty , char * dryRun , char * fieldManager , int force );


// read the specified CSIDriver
//
v1beta1_csi_driver_t*
StorageV1beta1API_readCSIDriver(apiClient_t *apiClient, char * name , char * pretty , int exact , int export );


// read the specified CSINode
//
v1beta1_csi_node_t*
StorageV1beta1API_readCSINode(apiClient_t *apiClient, char * name , char * pretty , int exact , int export );


// read the specified StorageClass
//
v1beta1_storage_class_t*
StorageV1beta1API_readStorageClass(apiClient_t *apiClient, char * name , char * pretty , int exact , int export );


// read the specified VolumeAttachment
//
v1beta1_volume_attachment_t*
StorageV1beta1API_readVolumeAttachment(apiClient_t *apiClient, char * name , char * pretty , int exact , int export );


// replace the specified CSIDriver
//
v1beta1_csi_driver_t*
StorageV1beta1API_replaceCSIDriver(apiClient_t *apiClient, char * name , v1beta1_csi_driver_t * body , char * pretty , char * dryRun , char * fieldManager );


// replace the specified CSINode
//
v1beta1_csi_node_t*
StorageV1beta1API_replaceCSINode(apiClient_t *apiClient, char * name , v1beta1_csi_node_t * body , char * pretty , char * dryRun , char * fieldManager );


// replace the specified StorageClass
//
v1beta1_storage_class_t*
StorageV1beta1API_replaceStorageClass(apiClient_t *apiClient, char * name , v1beta1_storage_class_t * body , char * pretty , char * dryRun , char * fieldManager );


// replace the specified VolumeAttachment
//
v1beta1_volume_attachment_t*
StorageV1beta1API_replaceVolumeAttachment(apiClient_t *apiClient, char * name , v1beta1_volume_attachment_t * body , char * pretty , char * dryRun , char * fieldManager );


