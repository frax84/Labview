<?xml version='1.0' encoding='UTF-8'?>
<Project Type="Project" LVVersion="14008000">
	<Item Name="My Computer" Type="My Computer">
		<Property Name="NI.SortType" Type="Int">3</Property>
		<Property Name="server.app.propertiesEnabled" Type="Bool">true</Property>
		<Property Name="server.control.propertiesEnabled" Type="Bool">true</Property>
		<Property Name="server.tcp.enabled" Type="Bool">false</Property>
		<Property Name="server.tcp.port" Type="Int">0</Property>
		<Property Name="server.tcp.serviceName" Type="Str">My Computer/VI Server</Property>
		<Property Name="server.tcp.serviceName.default" Type="Str">My Computer/VI Server</Property>
		<Property Name="server.vi.callsEnabled" Type="Bool">true</Property>
		<Property Name="server.vi.propertiesEnabled" Type="Bool">true</Property>
		<Property Name="specify.custom.address" Type="Bool">false</Property>
		<Item Name="Motor management" Type="Folder">
			<Item Name="Typedef" Type="Folder">
				<Item Name="States - PC.ctl" Type="VI" URL="../Motor Management/Typedef/States - PC.ctl"/>
				<Item Name="Management variables.ctl" Type="VI" URL="../Motor Management/Typedef/Management variables.ctl"/>
				<Item Name="Process scheduler - Commands.ctl" Type="VI" URL="../Motor Management/Typedef/Process scheduler - Commands.ctl"/>
			</Item>
			<Item Name="SubVIs" Type="Folder">
				<Item Name="Motor planner.vi" Type="VI" URL="../Motor Management/SubVIs/Motor planner.vi"/>
				<Item Name="Wait for ACK.vi" Type="VI" URL="../Motor Management/SubVIs/Wait for ACK.vi"/>
				<Item Name="Simple Cycle.vi" Type="VI" URL="../Motor Management/SubVIs/Simple Cycle.vi"/>
			</Item>
			<Item Name="Controls" Type="Folder">
				<Item Name="Up.ctl" Type="VI" URL="../Motor Management/Controls/Up.ctl"/>
				<Item Name="Right.ctl" Type="VI" URL="../Motor Management/Controls/Right.ctl"/>
				<Item Name="Left.ctl" Type="VI" URL="../Motor Management/Controls/Left.ctl"/>
				<Item Name="Down.ctl" Type="VI" URL="../Motor Management/Controls/Down.ctl"/>
			</Item>
			<Item Name="Motor Manager.vi" Type="VI" URL="../Motor Management/Motor Manager.vi"/>
		</Item>
		<Item Name="Arduino Firmware" Type="Folder">
			<Item Name="LV_interface.cpp" Type="Document" URL="../Motor_firmware/LV_interface.cpp"/>
			<Item Name="LV_interface.h" Type="Document" URL="../Motor_firmware/LV_interface.h"/>
			<Item Name="Motor_firmware.ino" Type="Document" URL="../Motor_firmware/Motor_firmware.ino"/>
		</Item>
		<Item Name="Motor manager.lvlib" Type="Library" URL="../LV Library/Motor manager.lvlib"/>
		<Item Name="Dependencies" Type="Dependencies">
			<Item Name="vi.lib" Type="Folder">
				<Item Name="VISA Configure Serial Port (Serial Instr).vi" Type="VI" URL="/&lt;vilib&gt;/Instr/_visa.llb/VISA Configure Serial Port (Serial Instr).vi"/>
				<Item Name="VISA Configure Serial Port (Instr).vi" Type="VI" URL="/&lt;vilib&gt;/Instr/_visa.llb/VISA Configure Serial Port (Instr).vi"/>
				<Item Name="VISA Configure Serial Port" Type="VI" URL="/&lt;vilib&gt;/Instr/_visa.llb/VISA Configure Serial Port"/>
			</Item>
			<Item Name="Move type.ctl" Type="VI" URL="../Typedef/Move type.ctl"/>
			<Item Name="Set distance.vi" Type="VI" URL="../SubVI/Set distance.vi"/>
			<Item Name="Set movement type.vi" Type="VI" URL="../SubVI/Set movement type.vi"/>
			<Item Name="Start-stop.vi" Type="VI" URL="../SubVI/Start-stop.vi"/>
			<Item Name="Set speed.vi" Type="VI" URL="../SubVI/Set speed.vi"/>
		</Item>
		<Item Name="Build Specifications" Type="Build">
			<Item Name="My Application" Type="EXE">
				<Property Name="App_copyErrors" Type="Bool">true</Property>
				<Property Name="App_INI_aliasGUID" Type="Str">{082E40A5-3CD9-401F-9DB8-24668B6FDDBA}</Property>
				<Property Name="App_INI_GUID" Type="Str">{42A67506-9D32-41CB-AAEF-E4A05AF849FB}</Property>
				<Property Name="App_serverConfig.httpPort" Type="Int">8002</Property>
				<Property Name="Bld_autoIncrement" Type="Bool">true</Property>
				<Property Name="Bld_buildCacheID" Type="Str">{D0190A14-E097-4C06-9E72-D4DD2D8EA795}</Property>
				<Property Name="Bld_buildSpecName" Type="Str">My Application</Property>
				<Property Name="Bld_excludeInlineSubVIs" Type="Bool">true</Property>
				<Property Name="Bld_excludeLibraryItems" Type="Bool">true</Property>
				<Property Name="Bld_excludePolymorphicVIs" Type="Bool">true</Property>
				<Property Name="Bld_localDestDir" Type="Path">../builds/NI_AB_PROJECTNAME/My Application</Property>
				<Property Name="Bld_localDestDirType" Type="Str">relativeToCommon</Property>
				<Property Name="Bld_modifyLibraryFile" Type="Bool">true</Property>
				<Property Name="Bld_previewCacheID" Type="Str">{4123B7A5-74CC-4ED2-8464-847F8BA9AC1D}</Property>
				<Property Name="Bld_version.build" Type="Int">1</Property>
				<Property Name="Bld_version.major" Type="Int">1</Property>
				<Property Name="Destination[0].destName" Type="Str">Motor Control.exe</Property>
				<Property Name="Destination[0].path" Type="Path">../builds/NI_AB_PROJECTNAME/My Application/Motor Control.exe</Property>
				<Property Name="Destination[0].preserveHierarchy" Type="Bool">true</Property>
				<Property Name="Destination[0].type" Type="Str">App</Property>
				<Property Name="Destination[1].destName" Type="Str">Support Directory</Property>
				<Property Name="Destination[1].path" Type="Path">../builds/NI_AB_PROJECTNAME/My Application/data</Property>
				<Property Name="DestinationCount" Type="Int">2</Property>
				<Property Name="Source[0].itemID" Type="Str">{B66473C6-CF5B-4F69-8CED-5BB77F1B4A32}</Property>
				<Property Name="Source[0].type" Type="Str">Container</Property>
				<Property Name="Source[1].Container.applyInclusion" Type="Bool">true</Property>
				<Property Name="Source[1].Container.depDestIndex" Type="Int">0</Property>
				<Property Name="Source[1].destinationIndex" Type="Int">0</Property>
				<Property Name="Source[1].itemID" Type="Ref">/My Computer/Motor management/Typedef</Property>
				<Property Name="Source[1].sourceInclusion" Type="Str">Include</Property>
				<Property Name="Source[1].type" Type="Str">Container</Property>
				<Property Name="Source[2].Container.applyInclusion" Type="Bool">true</Property>
				<Property Name="Source[2].Container.depDestIndex" Type="Int">0</Property>
				<Property Name="Source[2].destinationIndex" Type="Int">0</Property>
				<Property Name="Source[2].itemID" Type="Ref">/My Computer/Motor management/SubVIs</Property>
				<Property Name="Source[2].sourceInclusion" Type="Str">Include</Property>
				<Property Name="Source[2].type" Type="Str">Container</Property>
				<Property Name="Source[3].Container.applyInclusion" Type="Bool">true</Property>
				<Property Name="Source[3].Container.depDestIndex" Type="Int">0</Property>
				<Property Name="Source[3].destinationIndex" Type="Int">0</Property>
				<Property Name="Source[3].itemID" Type="Ref">/My Computer/Motor management/Controls</Property>
				<Property Name="Source[3].sourceInclusion" Type="Str">Include</Property>
				<Property Name="Source[3].type" Type="Str">Container</Property>
				<Property Name="Source[4].destinationIndex" Type="Int">0</Property>
				<Property Name="Source[4].itemID" Type="Ref">/My Computer/Motor management/Motor Manager.vi</Property>
				<Property Name="Source[4].sourceInclusion" Type="Str">TopLevel</Property>
				<Property Name="Source[4].type" Type="Str">VI</Property>
				<Property Name="Source[5].Container.applyInclusion" Type="Bool">true</Property>
				<Property Name="Source[5].Container.depDestIndex" Type="Int">0</Property>
				<Property Name="Source[5].destinationIndex" Type="Int">0</Property>
				<Property Name="Source[5].itemID" Type="Ref">/My Computer/Arduino Firmware</Property>
				<Property Name="Source[5].sourceInclusion" Type="Str">Include</Property>
				<Property Name="Source[5].type" Type="Str">Container</Property>
				<Property Name="Source[6].destinationIndex" Type="Int">0</Property>
				<Property Name="Source[6].itemID" Type="Ref">/My Computer/Motor manager.lvlib</Property>
				<Property Name="Source[6].Library.allowMissingMembers" Type="Bool">true</Property>
				<Property Name="Source[6].sourceInclusion" Type="Str">Include</Property>
				<Property Name="Source[6].type" Type="Str">Library</Property>
				<Property Name="SourceCount" Type="Int">7</Property>
				<Property Name="TgtF_fileDescription" Type="Str">My Application</Property>
				<Property Name="TgtF_internalName" Type="Str">My Application</Property>
				<Property Name="TgtF_legalCopyright" Type="Str">Copyright © 2017 </Property>
				<Property Name="TgtF_productName" Type="Str">My Application</Property>
				<Property Name="TgtF_targetfileGUID" Type="Str">{CC21D521-9268-45F5-B6BA-4CEDFC225CA0}</Property>
				<Property Name="TgtF_targetfileName" Type="Str">Motor Control.exe</Property>
			</Item>
		</Item>
	</Item>
</Project>
