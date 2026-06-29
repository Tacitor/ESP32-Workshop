#ifndef ESP_BLE_h
#define ESP_BLE_h

// BLE function declarations
/**
 * Transmit a string over BLE and send a notify.
 * NOTE: notify() only sends up the first 20 bytes and the rest is discarded I think?
 */
void tx_BT(String str);

#endif