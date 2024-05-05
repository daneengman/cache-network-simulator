# Begin_DVE_Session_Save_Info
# DVE restart session
# Saved on Sat May 4 22:41:35 2024
# Designs open: 1
#   Sim: /afs/ece.cmu.edu/usr/dengman/private/cache-network-simulator/cadss/simv
# Toplevel windows open: 2
# 	TopLevel.1
# 	TopLevel.2
#   Source.1: NetworkPkg
#   Wave.1: 130 signals
#   Group count = 12
#   Group cadss_interconnect signal count = 15
#   Group divider signal count = 7
#   Group interconnect signal count = 13
#   Group genblk1[0].n signal count = 12
#   Group genblk1[1].n signal count = 12
#   Group genblk1[2].n signal count = 12
#   Group genblk1[3].n signal count = 12
#   Group genblk1[4].n signal count = 12
#   Group genblk1[5].n signal count = 12
#   Group genblk1[6].n signal count = 12
#   Group genblk1[7].n signal count = 11
#   Group NetworkPkg signal count = 0
# End_DVE_Session_Save_Info

# DVE version: K-2015.09_Full64
# DVE build date: Aug 25 2015 21:36:02


#<Session mode="Restart" path=".restartSimSession.tcl" type="Debug">

gui_set_loading_session_type Restart
gui_continuetime_set
gui_clear_window -type Wave
gui_clear_window -type List

# Application preferences
gui_set_pref_value -key app_default_font -value {Helvetica,10,-1,5,50,0,0,0,0,0}
gui_src_preferences -tabstop 8 -maxbits 24 -windownumber 1
#<WindowLayout>

# DVE top-level session


# Create and position top-level window: TopLevel.1

set TopLevel.1 TopLevel.1

# Docked window settings
set HSPane.1 HSPane.1
set Hier.1 Hier.1
set Stack.1 Stack.1
set Class.1 Class.1
set Object.1 Object.1
set DLPane.1 DLPane.1
set Data.1 Data.1
set Local.1 Local.1
set Member.1 Member.1
gui_sync_global -id ${TopLevel.1} -option true

# MDI window settings
set Console.1 Console.1
gui_update_layout -id ${Console.1} {{show_state maximized} {dock_state undocked} {dock_on_new_line false}}
set Source.1 Source.1
gui_update_layout -id ${Source.1} {{show_state maximized} {dock_state undocked} {dock_on_new_line false}}

# End MDI window settings


# Create and position top-level window: TopLevel.2

set TopLevel.2 TopLevel.2

# Docked window settings
gui_sync_global -id ${TopLevel.2} -option true

# MDI window settings
set Wave.1 Wave.1
gui_update_layout -id ${Wave.1} {{show_state maximized} {dock_state undocked} {dock_on_new_line false} {child_wave_left 459} {child_wave_right 1120} {child_wave_colname 227} {child_wave_colvalue 227} {child_wave_col1 0} {child_wave_col2 1}}

# End MDI window settings


#</WindowLayout>

#<Database>

gui_set_precision 1s
gui_set_time_units 1s
#</Database>

# DVE Global setting session: 


# Global: Breakpoints

# Global: Bus

# Global: Expressions

# Global: Signal Time Shift

# Global: Signal Compare

# Global: Signal Groups
gui_load_child_values {cadss_interconnect.interconnect}
gui_load_child_values {cadss_interconnect}
gui_load_child_values {cadss_interconnect.interconnect.genblk1[0].n}
gui_load_child_values {cadss_interconnect.interconnect.genblk1[1].n}
gui_load_child_values {cadss_interconnect.interconnect.genblk1[2].n}
gui_load_child_values {cadss_interconnect.interconnect.genblk1[3].n}
gui_load_child_values {cadss_interconnect.divider}
gui_load_child_values {cadss_interconnect.interconnect.genblk1[4].n}
gui_load_child_values {cadss_interconnect.interconnect.genblk1[5].n}
gui_load_child_values {cadss_interconnect.interconnect.genblk1[6].n}
gui_load_child_values {cadss_interconnect.interconnect.genblk1[7].n}


set _session_group_1 cadss_interconnect
gui_sg_create "$_session_group_1"
set cadss_interconnect "$_session_group_1"

gui_sg_addsignal -group "$_session_group_1" { cadss_interconnect.request_out_avail cadss_interconnect.processed_request cadss_interconnect.interconnect_clk cadss_interconnect.NUM_PROC cadss_interconnect.request_in_avail cadss_interconnect.new_request cadss_interconnect.request cadss_interconnect.packetReceived cadss_interconnect.packetSendIn cadss_interconnect.SERVER_PORT cadss_interconnect.core_clk cadss_interconnect.inFlight cadss_interconnect.rst_l cadss_interconnect.finished_request cadss_interconnect.tickCount }
gui_set_radix -radix {decimal} -signals {Sim:cadss_interconnect.NUM_PROC}
gui_set_radix -radix {twosComplement} -signals {Sim:cadss_interconnect.NUM_PROC}
gui_set_radix -radix {decimal} -signals {Sim:cadss_interconnect.SERVER_PORT}
gui_set_radix -radix {twosComplement} -signals {Sim:cadss_interconnect.SERVER_PORT}
gui_set_radix -radix {decimal} -signals {Sim:cadss_interconnect.inFlight}
gui_set_radix -radix {twosComplement} -signals {Sim:cadss_interconnect.inFlight}
gui_set_radix -radix {decimal} -signals {Sim:cadss_interconnect.tickCount}
gui_set_radix -radix {twosComplement} -signals {Sim:cadss_interconnect.tickCount}

set _session_group_2 divider
gui_sg_create "$_session_group_2"
set divider "$_session_group_2"

gui_sg_addsignal -group "$_session_group_2" { cadss_interconnect.divider.clk_in cadss_interconnect.divider.rst_l cadss_interconnect.divider.clk_out cadss_interconnect.divider.count cadss_interconnect.divider.divided_clock cadss_interconnect.divider.RATIO {cadss_interconnect.divider.$unit} }
gui_set_radix -radix {decimal} -signals {Sim:cadss_interconnect.divider.RATIO}
gui_set_radix -radix {twosComplement} -signals {Sim:cadss_interconnect.divider.RATIO}

set _session_group_3 interconnect
gui_sg_create "$_session_group_3"
set interconnect "$_session_group_3"

gui_sg_addsignal -group "$_session_group_3" { cadss_interconnect.interconnect.packetNodeRec cadss_interconnect.interconnect.packetSendNext cadss_interconnect.interconnect.NUM_PROC cadss_interconnect.interconnect.packetOut cadss_interconnect.interconnect.packetSendIn cadss_interconnect.interconnect.packetCoreIn cadss_interconnect.interconnect.full cadss_interconnect.interconnect.clk cadss_interconnect.interconnect.rst_l cadss_interconnect.interconnect.packetRecieved cadss_interconnect.interconnect.packetIn cadss_interconnect.interconnect.recieved cadss_interconnect.interconnect.recievedOut }
gui_set_radix -radix {decimal} -signals {Sim:cadss_interconnect.interconnect.NUM_PROC}
gui_set_radix -radix {twosComplement} -signals {Sim:cadss_interconnect.interconnect.NUM_PROC}

set _session_group_4 {genblk1[0].n}
gui_sg_create "$_session_group_4"
set {genblk1[0].n} "$_session_group_4"

gui_sg_addsignal -group "$_session_group_4" { {cadss_interconnect.interconnect.genblk1[0].n.nodeID} {cadss_interconnect.interconnect.genblk1[0].n.clk} {cadss_interconnect.interconnect.genblk1[0].n.rst_l} {cadss_interconnect.interconnect.genblk1[0].n.packetSendIn} {cadss_interconnect.interconnect.genblk1[0].n.packetIn} {cadss_interconnect.interconnect.genblk1[0].n.packetSendNext} {cadss_interconnect.interconnect.genblk1[0].n.packetOut} {cadss_interconnect.interconnect.genblk1[0].n.packetRecieved} {cadss_interconnect.interconnect.genblk1[0].n.recieved} {cadss_interconnect.interconnect.genblk1[0].n.full} {cadss_interconnect.interconnect.genblk1[0].n.empty} {cadss_interconnect.interconnect.genblk1[0].n.$unit} }

set _session_group_5 {genblk1[1].n}
gui_sg_create "$_session_group_5"
set {genblk1[1].n} "$_session_group_5"

gui_sg_addsignal -group "$_session_group_5" { {cadss_interconnect.interconnect.genblk1[1].n.nodeID} {cadss_interconnect.interconnect.genblk1[1].n.clk} {cadss_interconnect.interconnect.genblk1[1].n.rst_l} {cadss_interconnect.interconnect.genblk1[1].n.packetSendIn} {cadss_interconnect.interconnect.genblk1[1].n.packetIn} {cadss_interconnect.interconnect.genblk1[1].n.packetSendNext} {cadss_interconnect.interconnect.genblk1[1].n.packetOut} {cadss_interconnect.interconnect.genblk1[1].n.packetRecieved} {cadss_interconnect.interconnect.genblk1[1].n.recieved} {cadss_interconnect.interconnect.genblk1[1].n.full} {cadss_interconnect.interconnect.genblk1[1].n.empty} {cadss_interconnect.interconnect.genblk1[1].n.$unit} }

set _session_group_6 {genblk1[2].n}
gui_sg_create "$_session_group_6"
set {genblk1[2].n} "$_session_group_6"

gui_sg_addsignal -group "$_session_group_6" { {cadss_interconnect.interconnect.genblk1[2].n.nodeID} {cadss_interconnect.interconnect.genblk1[2].n.clk} {cadss_interconnect.interconnect.genblk1[2].n.rst_l} {cadss_interconnect.interconnect.genblk1[2].n.packetSendIn} {cadss_interconnect.interconnect.genblk1[2].n.packetIn} {cadss_interconnect.interconnect.genblk1[2].n.packetSendNext} {cadss_interconnect.interconnect.genblk1[2].n.packetOut} {cadss_interconnect.interconnect.genblk1[2].n.packetRecieved} {cadss_interconnect.interconnect.genblk1[2].n.recieved} {cadss_interconnect.interconnect.genblk1[2].n.full} {cadss_interconnect.interconnect.genblk1[2].n.empty} {cadss_interconnect.interconnect.genblk1[2].n.$unit} }

set _session_group_7 {genblk1[3].n}
gui_sg_create "$_session_group_7"
set {genblk1[3].n} "$_session_group_7"

gui_sg_addsignal -group "$_session_group_7" { {cadss_interconnect.interconnect.genblk1[3].n.nodeID} {cadss_interconnect.interconnect.genblk1[3].n.clk} {cadss_interconnect.interconnect.genblk1[3].n.rst_l} {cadss_interconnect.interconnect.genblk1[3].n.packetSendIn} {cadss_interconnect.interconnect.genblk1[3].n.packetIn} {cadss_interconnect.interconnect.genblk1[3].n.packetSendNext} {cadss_interconnect.interconnect.genblk1[3].n.packetOut} {cadss_interconnect.interconnect.genblk1[3].n.packetRecieved} {cadss_interconnect.interconnect.genblk1[3].n.recieved} {cadss_interconnect.interconnect.genblk1[3].n.full} {cadss_interconnect.interconnect.genblk1[3].n.empty} {cadss_interconnect.interconnect.genblk1[3].n.$unit} }

set _session_group_8 {genblk1[4].n}
gui_sg_create "$_session_group_8"
set {genblk1[4].n} "$_session_group_8"

gui_sg_addsignal -group "$_session_group_8" { {cadss_interconnect.interconnect.genblk1[4].n.nodeID} {cadss_interconnect.interconnect.genblk1[4].n.clk} {cadss_interconnect.interconnect.genblk1[4].n.rst_l} {cadss_interconnect.interconnect.genblk1[4].n.packetSendIn} {cadss_interconnect.interconnect.genblk1[4].n.packetIn} {cadss_interconnect.interconnect.genblk1[4].n.packetSendNext} {cadss_interconnect.interconnect.genblk1[4].n.packetOut} {cadss_interconnect.interconnect.genblk1[4].n.packetRecieved} {cadss_interconnect.interconnect.genblk1[4].n.recieved} {cadss_interconnect.interconnect.genblk1[4].n.full} {cadss_interconnect.interconnect.genblk1[4].n.empty} {cadss_interconnect.interconnect.genblk1[4].n.$unit} }

set _session_group_9 {genblk1[5].n}
gui_sg_create "$_session_group_9"
set {genblk1[5].n} "$_session_group_9"

gui_sg_addsignal -group "$_session_group_9" { {cadss_interconnect.interconnect.genblk1[5].n.nodeID} {cadss_interconnect.interconnect.genblk1[5].n.clk} {cadss_interconnect.interconnect.genblk1[5].n.rst_l} {cadss_interconnect.interconnect.genblk1[5].n.packetSendIn} {cadss_interconnect.interconnect.genblk1[5].n.packetIn} {cadss_interconnect.interconnect.genblk1[5].n.packetSendNext} {cadss_interconnect.interconnect.genblk1[5].n.packetOut} {cadss_interconnect.interconnect.genblk1[5].n.packetRecieved} {cadss_interconnect.interconnect.genblk1[5].n.recieved} {cadss_interconnect.interconnect.genblk1[5].n.full} {cadss_interconnect.interconnect.genblk1[5].n.empty} {cadss_interconnect.interconnect.genblk1[5].n.$unit} }

set _session_group_10 {genblk1[6].n}
gui_sg_create "$_session_group_10"
set {genblk1[6].n} "$_session_group_10"

gui_sg_addsignal -group "$_session_group_10" { {cadss_interconnect.interconnect.genblk1[6].n.nodeID} {cadss_interconnect.interconnect.genblk1[6].n.clk} {cadss_interconnect.interconnect.genblk1[6].n.rst_l} {cadss_interconnect.interconnect.genblk1[6].n.packetSendIn} {cadss_interconnect.interconnect.genblk1[6].n.packetIn} {cadss_interconnect.interconnect.genblk1[6].n.packetSendNext} {cadss_interconnect.interconnect.genblk1[6].n.packetOut} {cadss_interconnect.interconnect.genblk1[6].n.packetRecieved} {cadss_interconnect.interconnect.genblk1[6].n.recieved} {cadss_interconnect.interconnect.genblk1[6].n.full} {cadss_interconnect.interconnect.genblk1[6].n.empty} {cadss_interconnect.interconnect.genblk1[6].n.$unit} }

set _session_group_11 {genblk1[7].n}
gui_sg_create "$_session_group_11"
set {genblk1[7].n} "$_session_group_11"

gui_sg_addsignal -group "$_session_group_11" { {cadss_interconnect.interconnect.genblk1[7].n.nodeID} {cadss_interconnect.interconnect.genblk1[7].n.packetSendNext} {cadss_interconnect.interconnect.genblk1[7].n.packetOut} {cadss_interconnect.interconnect.genblk1[7].n.empty} {cadss_interconnect.interconnect.genblk1[7].n.packetSendIn} {cadss_interconnect.interconnect.genblk1[7].n.full} {cadss_interconnect.interconnect.genblk1[7].n.clk} {cadss_interconnect.interconnect.genblk1[7].n.rst_l} {cadss_interconnect.interconnect.genblk1[7].n.packetRecieved} {cadss_interconnect.interconnect.genblk1[7].n.packetIn} {cadss_interconnect.interconnect.genblk1[7].n.recieved} }

set _session_group_12 NetworkPkg
gui_sg_create "$_session_group_12"
set NetworkPkg "$_session_group_12"


# Global: Highlighting

# Global: Stack
gui_change_stack_mode -mode list

# Post database loading setting...

# Save global setting...

# Wave/List view global setting
gui_cov_show_value -switch false

# Close all empty TopLevel windows
foreach __top [gui_ekki_get_window_ids -type TopLevel] {
    if { [llength [gui_ekki_get_window_ids -parent $__top]] == 0} {
        gui_close_window -window $__top
    }
}
gui_set_loading_session_type noSession
# DVE View/pane content session: 


# Hier 'Hier.1'
gui_show_window -window ${Hier.1}
gui_list_set_filter -id ${Hier.1} -list { {Package 1} {All 0} {Process 1} {VirtPowSwitch 0} {UnnamedProcess 1} {UDP 0} {Function 1} {Block 1} {SrsnAndSpaCell 0} {OVA Unit 1} {LeafScCell 1} {LeafVlgCell 1} {Interface 1} {LeafVhdCell 1} {$unit 1} {NamedBlock 1} {Task 1} {VlgPackage 1} {ClassDef 1} {VirtIsoCell 0} }
gui_list_set_filter -id ${Hier.1} -text {*}
gui_change_design -id ${Hier.1} -design Sim
catch {gui_list_select -id ${Hier.1} {cadss_interconnect}}
gui_view_scroll -id ${Hier.1} -vertical -set 0
gui_view_scroll -id ${Hier.1} -horizontal -set 0

# Class 'Class.1'
gui_list_set_filter -id ${Class.1} -list { {OVM 1} {VMM 1} {All 1} {Object 1} {UVM 1} {RVM 1} }
gui_list_set_filter -id ${Class.1} -text {*}
gui_change_design -id ${Class.1} -design Sim

# Member 'Member.1'
gui_list_set_filter -id ${Member.1} -list { {InternalMember 0} {RandMember 1} {All 0} {BaseMember 0} {PrivateMember 1} {LibBaseMember 0} {AutomaticMember 1} {VirtualMember 1} {PublicMember 1} {ProtectedMember 1} {OverRiddenMember 0} {InterfaceClassMember 1} {StaticMember 1} }
gui_list_set_filter -id ${Member.1} -text {*}

# Data 'Data.1'
gui_list_set_filter -id ${Data.1} -list { {Buffer 1} {Input 1} {Others 1} {Linkage 1} {Output 1} {LowPower 1} {Parameter 1} {All 1} {Aggregate 1} {LibBaseMember 1} {Event 1} {Assertion 1} {Constant 1} {Interface 1} {BaseMembers 1} {Signal 1} {$unit 1} {Inout 1} {Variable 1} }
gui_list_set_filter -id ${Data.1} -text {*}
gui_view_scroll -id ${Data.1} -vertical -set 0
gui_view_scroll -id ${Data.1} -horizontal -set 0
gui_view_scroll -id ${Hier.1} -vertical -set 0
gui_view_scroll -id ${Hier.1} -horizontal -set 0

# Source 'Source.1'
gui_src_value_annotate -id ${Source.1} -switch false
gui_set_env TOGGLE::VALUEANNOTATE 0
gui_open_source -id ${Source.1}  -replace -active NetworkPkg /afs/ece.cmu.edu/usr/dengman/private/cache-network-simulator/cadss/interconnectRingSV/sv/NetworkPkg.svg
gui_view_scroll -id ${Source.1} -vertical -set 0
gui_src_set_reusable -id ${Source.1}
# Warning: Class view not found.

# View 'Wave.1'
gui_wv_sync -id ${Wave.1} -switch false
set groupExD [gui_get_pref_value -category Wave -key exclusiveSG]
gui_set_pref_value -category Wave -key exclusiveSG -value {false}
set origWaveHeight [gui_get_pref_value -category Wave -key waveRowHeight]
gui_list_set_height -id Wave -height 25
set origGroupCreationState [gui_list_create_group_when_add -wave]
gui_list_create_group_when_add -wave -disable
gui_wv_zoom_timerange -id ${Wave.1} 4597 5331
gui_list_add_group -id ${Wave.1} -after {New Group} {cadss_interconnect}
gui_list_add_group -id ${Wave.1} -after {New Group} {divider}
gui_list_add_group -id ${Wave.1} -after {New Group} {interconnect}
gui_list_add_group -id ${Wave.1} -after {New Group} {{genblk1[0].n}}
gui_list_add_group -id ${Wave.1} -after {New Group} {{genblk1[1].n}}
gui_list_add_group -id ${Wave.1} -after {New Group} {{genblk1[2].n}}
gui_list_add_group -id ${Wave.1} -after {New Group} {{genblk1[3].n}}
gui_list_add_group -id ${Wave.1} -after {New Group} {{genblk1[4].n}}
gui_list_add_group -id ${Wave.1} -after {New Group} {{genblk1[5].n}}
gui_list_add_group -id ${Wave.1} -after {New Group} {{genblk1[6].n}}
gui_list_add_group -id ${Wave.1} -after {New Group} {{genblk1[7].n}}
gui_list_add_group -id ${Wave.1} -after {New Group} {NetworkPkg}
gui_list_select -id ${Wave.1} {cadss_interconnect.request_in_avail }
gui_seek_criteria -id ${Wave.1} {Any Edge}



gui_set_env TOGGLE::DEFAULT_WAVE_WINDOW ${Wave.1}
gui_set_pref_value -category Wave -key exclusiveSG -value $groupExD
gui_list_set_height -id Wave -height $origWaveHeight
if {$origGroupCreationState} {
	gui_list_create_group_when_add -wave -enable
}
if { $groupExD } {
 gui_msg_report -code DVWW028
}
gui_list_set_filter -id ${Wave.1} -list { {Buffer 1} {Input 1} {Others 1} {Linkage 1} {Output 1} {Parameter 1} {All 1} {Aggregate 1} {LibBaseMember 1} {Event 1} {Assertion 1} {Constant 1} {Interface 1} {BaseMembers 1} {Signal 1} {$unit 1} {Inout 1} {Variable 1} }
gui_list_set_filter -id ${Wave.1} -text {*}
gui_list_set_insertion_bar  -id ${Wave.1} -group NetworkPkg  -position in

gui_view_scroll -id ${Wave.1} -vertical -set 325
gui_show_grid -id ${Wave.1} -enable false
# Restore toplevel window zorder
# The toplevel window could be closed if it has no view/pane
if {[gui_exist_window -window ${TopLevel.1}]} {
	gui_set_active_window -window ${TopLevel.1}
	gui_set_active_window -window ${Source.1}
	gui_set_active_window -window ${HSPane.1}
}
if {[gui_exist_window -window ${TopLevel.2}]} {
	gui_set_active_window -window ${TopLevel.2}
	gui_set_active_window -window ${Wave.1}
}
#</Session>

