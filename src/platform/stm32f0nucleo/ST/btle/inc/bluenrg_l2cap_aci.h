/******************** (C) COPYRIGHT 2014 STMicroelectronics ********************
* File Name          : bluenrg_l2cap_aci.h
* Author             : AMS - HEA&RF BU
* Version            : V1.0.0
* Date               : 26-Jun-2014
* Description        : Header file with L2CAP commands for BlueNRG FW6.3.
********************************************************************************
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
* AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*******************************************************************************/

#ifndef __BLUENRG_L2CAP_ACI_H__
#define __BLUENRG_L2CAP_ACI_H__

/**
 *@defgroup L2CAP_Functions L2CAP functions
 *@brief API for L2CAP layer.
 *@{
 */

/**
 * @brief Send an L2CAP Connection Parameter Update request from the slave to the master.
 * @note  An @ref EVT_BLUE_L2CAP_CONN_UPD_RESP event will be raised when the master will respond to the request
 * 		  (accepts or rejects).
 * @param conn_handle Connection handle on which the connection parameter update request has to be sent.
 * @param interval_min Defines minimum value for the connection event interval in the following manner:
 *						connIntervalMin = interval_min x 1.25ms
 * @param interval_max Defines maximum value for the connection event interval in the following manner:
 * 						connIntervalMax = interval_max x 1.25ms
 * @param slave_latency Defines the slave latency parameter (number of connection events that can be skipped).
 * @param timeout_multiplier Defines connection timeout parameter in the following manner:
 * 							 timeout_multiplier x 10ms.
 * @return Value indicating success or error code.
 */
tBleStatus aci_l2cap_connection_parameter_update_request(uint16_t conn_handle,
							 uint16_t interval_min,
							 uint16_t interval_max,
							 uint16_t slave_latency,
							 uint16_t
							 timeout_multiplier);
/**
 * @brief Accept or reject a connection update.
 * @note  This command should be sent in response to a @ref EVT_BLUE_L2CAP_CONN_UPD_REQ event from the controller.
 * 		  The accept parameter has to be set if the connection parameters given in the event are acceptable.
 * @param conn_handle Handle received in @ref EVT_BLUE_L2CAP_CONN_UPD_REQ event.
 * @param interval_min
 * @param interval_max
 * @param slave_latency
 * @param timeout_multiplier
 * @param id
 * @param accept
 * @return
 */
tBleStatus aci_l2cap_connection_parameter_update_response(uint16_t conn_handle,
							  uint16_t interval_min,
							  uint16_t interval_max,
							  uint16_t
							  slave_latency,
							  uint16_t
							  timeout_multiplier,
							  uint8_t id,
							  uint8_t accept);

/**
 * @}
 */

/**
 * @defgroup L2CAP_Events L2CAP events
 * @{
 */

/**
 * This event is generated when the master responds to the L2CAP connection update request packet.
 * For more info see CONNECTION PARAMETER UPDATE RESPONSE in Bluetooth Core v4.0 spec.
 */
#define EVT_BLUE_L2CAP_CONN_UPD_RESP		  (0x0800)
typedef struct _evt_l2cap_conn_upd_resp {
	uint16_t conn_handle;
	uint8_t resp_len;
	uint8_t code;
		 /**< It will always be 0x13  */
	uint8_t identifier;
	uint16_t l2cap_length;
	uint16_t result;
} PACKED evt_l2cap_conn_upd_resp;

/**
 * This event is generated when the master does not respond to the connection update request
 * within 30 seconds.
 */
#define EVT_BLUE_L2CAP_PROCEDURE_TIMEOUT      (0x0801)

/**
 * The event is given by the L2CAP layer when a connection update request is received from the slave.
 * The application has to respond by calling aci_l2cap_connection_parameter_update_response().
 */
#define EVT_BLUE_L2CAP_CONN_UPD_REQ		  	  (0x0802)
typedef struct _evt_l2cap_conn_upd_req {
	uint16_t conn_handle;
	uint8_t resp_len;
	uint8_t code;
		 /**< It will always be 0x12  */
	uint8_t identifier;
	uint16_t l2cap_length;
	uint16_t interval_min;
	uint16_t interval_max;
	uint16_t slave_latency;
	uint16_t timeout_mult;
} PACKED evt_l2cap_conn_upd_req;

/**
 * @}
 */

#endif /* __BLUENRG_L2CAP_ACI_H__ */
