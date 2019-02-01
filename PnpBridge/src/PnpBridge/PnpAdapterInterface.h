// Copyright (c) Microsoft. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef PNPBRIDGE_PNP_ADAPTER_INTERFACE_H
#define PNPBRIDGE_PNP_ADAPTER_INTERFACE_H

#ifdef __cplusplus
extern "C"
{
#endif

typedef struct _PNPADAPTER_INTERFACE {
    PNP_INTERFACE_CLIENT_HANDLE Interface;
    void* Context;
    int key;
} PNPADAPTER_INTERFACE, *PPNPADAPTER_INTERFACE;

typedef void* PNPADAPTER_INTERFACE_HANDLE;


/**
* @brief    PNPADAPTER_PNP_INTERFACE_INITIALIZE callback uses to initialize a pnp adapter.
*

* @param    adapterArgs           Json object containing pnp adapter parameters specified in config.
*
* @returns  integer greater than zero on success and other values on failure.
*/
typedef int(*PNPADAPTER_PNP_INTERFACE_INITIALIZE) (const char* adapterArgs);


/**
* @brief    PNPADAPTER_PNP_INTERFACE_SHUTDOWN callback to uninitialize the pnp adapter.
*

*
* @returns  integer greater than zero on success and other values on failure.
*/
typedef int(*PNPADAPTER_PNP_INTERFACE_SHUTDOWN)();

/**
* @brief    PNPADAPTER_BIND_PNP_INTERFACE callback is called to create a new azure pnp interface client.
*

* @param    pnpInterface               Handle to pnp adapter interface
*
* @param    pnpDeviceClientHandle      Handle to pnp device client
*
* @param    payload                    Payload containing device info that was discovered
*
* @returns  integer greater than zero on success and other values on failure.
*/
typedef int(*PNPADAPTER_BIND_PNP_INTERFACE)(PNPADAPTER_INTERFACE_HANDLE pnpInterface, PNP_DEVICE_CLIENT_HANDLE pnpDeviceClientHandle, PPNPBRIDGE_DEVICE_CHANGE_PAYLOAD payload);

/**
* @brief    PNPADAPTER_RELEASE_PNP_INTERFACE uninitializes the pnp interface.
*
* @remarks  For private preview, azure pnp adapter should call PnP_InterfaceClient_Destroy

* @param    pnpInterface    Handle to pnp adapter interface
*
* @returns  integer greater than zero on success and other values on failure.
*/
typedef int(*PNPADAPTER_RELEASE_PNP_INTERFACE)(PNPADAPTER_INTERFACE_HANDLE pnpInterface);


/**
* @brief    PnpAdapter_GetPnpInterfaceClient gets the Azure iot pnp interface client handle

* @param    pnpInterface          Handle to pnp adapter interface
*
* @returns  Handle to Azure Pnp Interface client
*/
PNP_INTERFACE_CLIENT_HANDLE PnpAdapter_GetPnpInterfaceClient(PNPADAPTER_INTERFACE_HANDLE pnpInterface);

/**
* @brief    PnpAdapter_SetPnpInterfaceClient seta the Azure iot pnp interface client handle
*
* @remarks  This API is for private preview only. When PnpBridge calls CreatePnpInterface 
            callback on a pnp adapter, the adapter should create the Azure PnpInterfaceClient 
            using PnP_InterfaceClient_Create and then call PnpAdapter_SetPnpInterfaceClient with
            the PnpInterfaceClient

* @param    pnpInterface          Handle to pnp adapter interface
*
** @param   pnpInterfaceClient    Handle to Azure pnp interface client
*
* @returns  VOID
*/
void PnpAdapter_SetPnpInterfaceClient(PNPADAPTER_INTERFACE_HANDLE pnpInterface, PNP_INTERFACE_CLIENT_HANDLE pnpInterfaceClient);

/**
* @brief    PnpAdapter_SetContext sets a context for pnp adapter interface handle

* @param    pnpInterface          Handle to pnp adapter interface
*
* @param    Context               Pointer to a context
*
* @returns  integer greater than zero on success and other values on failure.
*/
int PnpAdapter_SetContext(PNPADAPTER_INTERFACE_HANDLE pnpInterface, void* context);

/**
* @brief    PnpAdapter_GetContext gets context set by pnp adapter.
*
* @remarks  PnpAdapter_GetContext is used to get the context set using PnpAdapter_SetContext

* @param    pnpInterface         Handle to pnp adapter interface
*
* @returns  void* context
*/
void* PnpAdapter_GetContext(PNPADAPTER_INTERFACE_HANDLE pnpInterface);

typedef struct _PNP_ADAPTER {
    // Identity of the Pnp Adapter that will be used in the config 
    // of a device under PnpParameters
    const char* Identity;
    PNPADAPTER_PNP_INTERFACE_INITIALIZE Initialize;
    PNPADAPTER_BIND_PNP_INTERFACE CreatePnpInterface;
    PNPADAPTER_RELEASE_PNP_INTERFACE ReleaseInterface;
    PNPADAPTER_PNP_INTERFACE_SHUTDOWN Shutdown;
} PNP_ADAPTER, *PPNP_ADAPTER;

#ifdef __cplusplus
}
#endif

#endif /* PNPBRIDGE_PNP_ADAPTER_INTERFACE_H */