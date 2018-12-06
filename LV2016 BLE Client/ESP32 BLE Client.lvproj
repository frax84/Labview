<?xml version='1.0' encoding='UTF-8'?>
<Project Type="Project" LVVersion="16008000">
	<Item Name="My Computer" Type="My Computer">
		<Property Name="server.app.propertiesEnabled" Type="Bool">true</Property>
		<Property Name="server.control.propertiesEnabled" Type="Bool">true</Property>
		<Property Name="server.tcp.enabled" Type="Bool">false</Property>
		<Property Name="server.tcp.port" Type="Int">0</Property>
		<Property Name="server.tcp.serviceName" Type="Str">My Computer/VI Server</Property>
		<Property Name="server.tcp.serviceName.default" Type="Str">My Computer/VI Server</Property>
		<Property Name="server.vi.callsEnabled" Type="Bool">true</Property>
		<Property Name="server.vi.propertiesEnabled" Type="Bool">true</Property>
		<Property Name="specify.custom.address" Type="Bool">false</Property>
		<Item Name="BLE modified VIs" Type="Folder" URL="../BLE modified VIs">
			<Property Name="NI.DISK" Type="Bool">true</Property>
		</Item>
		<Item Name="BLEConsoleApp" Type="Folder" URL="../BLEConsoleApp">
			<Property Name="NI.DISK" Type="Bool">true</Property>
		</Item>
		<Item Name="SubVIs" Type="Folder" URL="../SubVIs">
			<Property Name="NI.DISK" Type="Bool">true</Property>
		</Item>
		<Item Name="Typedef" Type="Folder" URL="../Typedef">
			<Property Name="NI.DISK" Type="Bool">true</Property>
		</Item>
		<Item Name="BLE CLient.lvlib" Type="Library" URL="../BLE CLient.lvlib"/>
		<Item Name="ESP32 BLE Client - Bluegiga.vi" Type="VI" URL="../ESP32 BLE Client - Bluegiga.vi"/>
		<Item Name="ESP32 BLE Client.vi" Type="VI" URL="../ESP32 BLE Client.vi"/>
		<Item Name="Dependencies" Type="Dependencies">
			<Item Name="user.lib" Type="Folder">
				<Item Name="BLE reference.ctl" Type="VI" URL="/&lt;userlib&gt;/National Instruments/BLE Instrument Drivers/BLE reference.ctl"/>
				<Item Name="Close BLE.vi" Type="VI" URL="/&lt;userlib&gt;/National Instruments/BLE Instrument Drivers/Close BLE.vi"/>
				<Item Name="Discover BLE.vi" Type="VI" URL="/&lt;userlib&gt;/National Instruments/BLE Instrument Drivers/Discover BLE.vi"/>
				<Item Name="Headers to Error Cluster.vi" Type="VI" URL="/&lt;userlib&gt;/National Instruments/BLE Instrument Drivers/Utility VIs/Headers to Error Cluster.vi"/>
				<Item Name="Initialize BLE.vi" Type="VI" URL="/&lt;userlib&gt;/National Instruments/BLE Instrument Drivers/Initialize BLE.vi"/>
			</Item>
			<Item Name="vi.lib" Type="Folder">
				<Item Name="address_type.ctl" Type="VI" URL="/&lt;vilib&gt;/BLE/type_def/address_type.ctl"/>
				<Item Name="advertising_package_type.ctl" Type="VI" URL="/&lt;vilib&gt;/BLE/type_def/advertising_package_type.ctl"/>
				<Item Name="Application Directory.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/file.llb/Application Directory.vi"/>
				<Item Name="ble_attach_dongle.vi" Type="VI" URL="/&lt;vilib&gt;/BLE/ble_functions/ble_attach_dongle.vi"/>
				<Item Name="ble_check_payload_error.vi" Type="VI" URL="/&lt;vilib&gt;/BLE/support_vi/ble_check_payload_error.vi"/>
				<Item Name="ble_cmd_attclient_find_information.vi" Type="VI" URL="/&lt;vilib&gt;/BLE/api_commands/ble_cmd_attclient_find_information.vi"/>
				<Item Name="ble_cmd_attclient_read_by_group_type.vi" Type="VI" URL="/&lt;vilib&gt;/BLE/api_commands/ble_cmd_attclient_read_by_group_type.vi"/>
				<Item Name="ble_cmd_attclient_read_by_handle.vi" Type="VI" URL="/&lt;vilib&gt;/BLE/api_commands/ble_cmd_attclient_read_by_handle.vi"/>
				<Item Name="ble_cmd_connection_disconnect.vi" Type="VI" URL="/&lt;vilib&gt;/BLE/api_commands/ble_cmd_connection_disconnect.vi"/>
				<Item Name="ble_cmd_end_procedure.vi" Type="VI" URL="/&lt;vilib&gt;/BLE/api_commands/ble_cmd_end_procedure.vi"/>
				<Item Name="ble_cmd_gap_connect_direct.vi" Type="VI" URL="/&lt;vilib&gt;/BLE/api_commands/ble_cmd_gap_connect_direct.vi"/>
				<Item Name="ble_cmd_gap_discover.vi" Type="VI" URL="/&lt;vilib&gt;/BLE/api_commands/ble_cmd_gap_discover.vi"/>
				<Item Name="ble_cmd_gap_set_scan_parameters.vi" Type="VI" URL="/&lt;vilib&gt;/BLE/api_commands/ble_cmd_gap_set_scan_parameters.vi"/>
				<Item Name="ble_cmd_system_get_info.vi" Type="VI" URL="/&lt;vilib&gt;/BLE/api_commands/ble_cmd_system_get_info.vi"/>
				<Item Name="ble_cmd_system_reset.vi" Type="VI" URL="/&lt;vilib&gt;/BLE/api_commands/ble_cmd_system_reset.vi"/>
				<Item Name="ble_connect_to_device.vi" Type="VI" URL="/&lt;vilib&gt;/BLE/ble_functions/ble_connect_to_device.vi"/>
				<Item Name="ble_delete_repeated_scan_responses.vi" Type="VI" URL="/&lt;vilib&gt;/BLE/support_vi/ble_delete_repeated_scan_responses.vi"/>
				<Item Name="ble_disconnect_device.vi" Type="VI" URL="/&lt;vilib&gt;/BLE/ble_functions/ble_disconnect_device.vi"/>
				<Item Name="ble_discover_ble_devices.vi" Type="VI" URL="/&lt;vilib&gt;/BLE/ble_functions/ble_discover_ble_devices.vi"/>
				<Item Name="ble_discover_characteristics.vi" Type="VI" URL="/&lt;vilib&gt;/BLE/ble_functions/ble_discover_characteristics.vi"/>
				<Item Name="ble_discover_services.vi" Type="VI" URL="/&lt;vilib&gt;/BLE/ble_functions/ble_discover_services.vi"/>
				<Item Name="ble_discover_stop.vi" Type="VI" URL="/&lt;vilib&gt;/BLE/ble_functions/ble_discover_stop.vi"/>
				<Item Name="ble_dongle_info.vi" Type="VI" URL="/&lt;vilib&gt;/BLE/ble_functions/ble_dongle_info.vi"/>
				<Item Name="ble_evt_attclient_attribute_value.vi" Type="VI" URL="/&lt;vilib&gt;/BLE/api_commands/ble_evt_attclient_attribute_value.vi"/>
				<Item Name="ble_evt_attclient_find_information_found.vi" Type="VI" URL="/&lt;vilib&gt;/BLE/api_commands/ble_evt_attclient_find_information_found.vi"/>
				<Item Name="ble_evt_attclient_group_found.vi" Type="VI" URL="/&lt;vilib&gt;/BLE/api_commands/ble_evt_attclient_group_found.vi"/>
				<Item Name="ble_evt_connection_disconnected.vi" Type="VI" URL="/&lt;vilib&gt;/BLE/api_commands/ble_evt_connection_disconnected.vi"/>
				<Item Name="ble_evt_connection_status.vi" Type="VI" URL="/&lt;vilib&gt;/BLE/api_commands/ble_evt_connection_status.vi"/>
				<Item Name="ble_evt_gap_scan_response.vi" Type="VI" URL="/&lt;vilib&gt;/BLE/api_commands/ble_evt_gap_scan_response.vi"/>
				<Item Name="ble_hex2string.vi" Type="VI" URL="/&lt;vilib&gt;/BLE/support_vi/ble_hex2string.vi"/>
				<Item Name="ble_parse_scan_response.vi" Type="VI" URL="/&lt;vilib&gt;/BLE/support_vi/ble_parse_scan_response.vi"/>
				<Item Name="ble_read_by_handle.vi" Type="VI" URL="/&lt;vilib&gt;/BLE/ble_functions/ble_read_by_handle.vi"/>
				<Item Name="ble_read_message.vi" Type="VI" URL="/&lt;vilib&gt;/BLE/support_vi/ble_read_message.vi"/>
				<Item Name="ble_read_specific_message.vi" Type="VI" URL="/&lt;vilib&gt;/BLE/support_vi/ble_read_specific_message.vi"/>
				<Item Name="ble_reset_dongle_and_cnx.vi" Type="VI" URL="/&lt;vilib&gt;/BLE/ble_functions/ble_reset_dongle_and_cnx.vi"/>
				<Item Name="ble_rsp_attclient_find_information.vi" Type="VI" URL="/&lt;vilib&gt;/BLE/api_commands/ble_rsp_attclient_find_information.vi"/>
				<Item Name="ble_rsp_attclient_read_by_group_type.vi" Type="VI" URL="/&lt;vilib&gt;/BLE/api_commands/ble_rsp_attclient_read_by_group_type.vi"/>
				<Item Name="ble_rsp_attclient_read_by_handle.vi" Type="VI" URL="/&lt;vilib&gt;/BLE/api_commands/ble_rsp_attclient_read_by_handle.vi"/>
				<Item Name="ble_rsp_connection_disconnect.vi" Type="VI" URL="/&lt;vilib&gt;/BLE/api_commands/ble_rsp_connection_disconnect.vi"/>
				<Item Name="ble_rsp_gap_connect_direct.vi" Type="VI" URL="/&lt;vilib&gt;/BLE/api_commands/ble_rsp_gap_connect_direct.vi"/>
				<Item Name="ble_rsp_gap_discover.vi" Type="VI" URL="/&lt;vilib&gt;/BLE/api_commands/ble_rsp_gap_discover.vi"/>
				<Item Name="ble_rsp_gap_end_procedure.vi" Type="VI" URL="/&lt;vilib&gt;/BLE/api_commands/ble_rsp_gap_end_procedure.vi"/>
				<Item Name="ble_rsp_gap_set_scan_parameters.vi" Type="VI" URL="/&lt;vilib&gt;/BLE/api_commands/ble_rsp_gap_set_scan_parameters.vi"/>
				<Item Name="ble_rsp_system_get_info.vi" Type="VI" URL="/&lt;vilib&gt;/BLE/api_commands/ble_rsp_system_get_info.vi"/>
				<Item Name="ble_scan_parameters.vi" Type="VI" URL="/&lt;vilib&gt;/BLE/ble_functions/ble_scan_parameters.vi"/>
				<Item Name="ble_starts_discovery.vi" Type="VI" URL="/&lt;vilib&gt;/BLE/ble_functions/ble_starts_discovery.vi"/>
				<Item Name="ble_string2hex.vi" Type="VI" URL="/&lt;vilib&gt;/BLE/support_vi/ble_string2hex.vi"/>
				<Item Name="ble_wait_ms.vi" Type="VI" URL="/&lt;vilib&gt;/BLE/support_vi/ble_wait_ms.vi"/>
				<Item Name="ble_write_message.vi" Type="VI" URL="/&lt;vilib&gt;/BLE/support_vi/ble_write_message.vi"/>
				<Item Name="BuildHelpPath.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/BuildHelpPath.vi"/>
				<Item Name="Check if File or Folder Exists.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/libraryn.llb/Check if File or Folder Exists.vi"/>
				<Item Name="Check Special Tags.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Check Special Tags.vi"/>
				<Item Name="Clear Errors.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Clear Errors.vi"/>
				<Item Name="connection_status_bundle.ctl" Type="VI" URL="/&lt;vilib&gt;/BLE/type_def/connection_status_bundle.ctl"/>
				<Item Name="Convert property node font to graphics font.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Convert property node font to graphics font.vi"/>
				<Item Name="Details Display Dialog.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Details Display Dialog.vi"/>
				<Item Name="DialogType.ctl" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/DialogType.ctl"/>
				<Item Name="DialogTypeEnum.ctl" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/DialogTypeEnum.ctl"/>
				<Item Name="Error Cluster From Error Code.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Error Cluster From Error Code.vi"/>
				<Item Name="Error Code Database.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Error Code Database.vi"/>
				<Item Name="ErrWarn.ctl" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/ErrWarn.ctl"/>
				<Item Name="eventvkey.ctl" Type="VI" URL="/&lt;vilib&gt;/event_ctls.llb/eventvkey.ctl"/>
				<Item Name="Find Tag.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Find Tag.vi"/>
				<Item Name="Format Message String.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Format Message String.vi"/>
				<Item Name="gap_discover_mode.ctl" Type="VI" URL="/&lt;vilib&gt;/BLE/type_def/gap_discover_mode.ctl"/>
				<Item Name="General Error Handler Core CORE.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/General Error Handler Core CORE.vi"/>
				<Item Name="General Error Handler.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/General Error Handler.vi"/>
				<Item Name="Get String Text Bounds.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Get String Text Bounds.vi"/>
				<Item Name="Get Text Rect.vi" Type="VI" URL="/&lt;vilib&gt;/picture/picture.llb/Get Text Rect.vi"/>
				<Item Name="GetHelpDir.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/GetHelpDir.vi"/>
				<Item Name="GetRTHostConnectedProp.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/GetRTHostConnectedProp.vi"/>
				<Item Name="LabVIEWHTTPClient.lvlib" Type="Library" URL="/&lt;vilib&gt;/httpClient/LabVIEWHTTPClient.lvlib"/>
				<Item Name="Longest Line Length in Pixels.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Longest Line Length in Pixels.vi"/>
				<Item Name="LVBoundsTypeDef.ctl" Type="VI" URL="/&lt;vilib&gt;/Utility/miscctls.llb/LVBoundsTypeDef.ctl"/>
				<Item Name="LVRectTypeDef.ctl" Type="VI" URL="/&lt;vilib&gt;/Utility/miscctls.llb/LVRectTypeDef.ctl"/>
				<Item Name="message_class.ctl" Type="VI" URL="/&lt;vilib&gt;/BLE/type_def/message_class.ctl"/>
				<Item Name="message_type.ctl" Type="VI" URL="/&lt;vilib&gt;/BLE/type_def/message_type.ctl"/>
				<Item Name="NI_FileType.lvlib" Type="Library" URL="/&lt;vilib&gt;/Utility/lvfile.llb/NI_FileType.lvlib"/>
				<Item Name="NI_PackedLibraryUtility.lvlib" Type="Library" URL="/&lt;vilib&gt;/Utility/LVLibp/NI_PackedLibraryUtility.lvlib"/>
				<Item Name="Not Found Dialog.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Not Found Dialog.vi"/>
				<Item Name="Path To Command Line String.vi" Type="VI" URL="/&lt;vilib&gt;/AdvancedString/Path To Command Line String.vi"/>
				<Item Name="PathToUNIXPathString.vi" Type="VI" URL="/&lt;vilib&gt;/Platform/CFURL.llb/PathToUNIXPathString.vi"/>
				<Item Name="scanning_technique.ctl" Type="VI" URL="/&lt;vilib&gt;/BLE/type_def/scanning_technique.ctl"/>
				<Item Name="Search and Replace Pattern.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Search and Replace Pattern.vi"/>
				<Item Name="service_type.ctl" Type="VI" URL="/&lt;vilib&gt;/BLE/type_def/service_type.ctl"/>
				<Item Name="Set Bold Text.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Set Bold Text.vi"/>
				<Item Name="Set String Value.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Set String Value.vi"/>
				<Item Name="Simple Error Handler.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Simple Error Handler.vi"/>
				<Item Name="System Exec.vi" Type="VI" URL="/&lt;vilib&gt;/Platform/system.llb/System Exec.vi"/>
				<Item Name="TagReturnType.ctl" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/TagReturnType.ctl"/>
				<Item Name="Three Button Dialog CORE.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Three Button Dialog CORE.vi"/>
				<Item Name="Three Button Dialog.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Three Button Dialog.vi"/>
				<Item Name="Trim Whitespace.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Trim Whitespace.vi"/>
				<Item Name="VISA Configure Serial Port" Type="VI" URL="/&lt;vilib&gt;/Instr/_visa.llb/VISA Configure Serial Port"/>
				<Item Name="VISA Configure Serial Port (Instr).vi" Type="VI" URL="/&lt;vilib&gt;/Instr/_visa.llb/VISA Configure Serial Port (Instr).vi"/>
				<Item Name="VISA Configure Serial Port (Serial Instr).vi" Type="VI" URL="/&lt;vilib&gt;/Instr/_visa.llb/VISA Configure Serial Port (Serial Instr).vi"/>
				<Item Name="whitespace.ctl" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/whitespace.ctl"/>
			</Item>
		</Item>
		<Item Name="Build Specifications" Type="Build"/>
	</Item>
</Project>
