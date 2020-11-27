# -*- coding: utf-8 -*-
#!/usr/bin/env python3

from bleak import BleakScanner

def main():
    targetName = "ESP_BLE_SECURITY"
    device = BleakScanner.discover(timeout= 5)

    print( device)




if __name__ == "__main__":
    main()

