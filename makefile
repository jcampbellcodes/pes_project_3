# Top level makefile. Delves into the Release and Debug subdirs and runs make on the specific targets contained.

# Builds all targets.
all: pc_debug

# Builds the PC release build.
pc_run:
	cd PC_Release && $(MAKE) output/pc_run

pc_debug:
	cd PC_Debug && $(MAKE) output/pc_debug

# Builds the PC release build.
pc_test:
	cd PC_Release_Test && $(MAKE) output/pc_test
	
pc_test_debug:
	cd PC_Debug_Test && $(MAKE) output/pc_test

# Builds the FB release build.
fb_run:
	cd KL25Z_Release && $(MAKE) output/pes_project3.axf

fb_debug:
	cd KL25Z_Debug && $(MAKE) output/pes_project3_debug.axf

fb_run_test:
	cd KL25Z_Release_Test && $(MAKE) output/pes_project3.axf

fb_debug_test:
	cd KL25Z_Debug_test && $(MAKE) output/pes_project3_debug.axf

# Cleans both Debug and Release areas.
clean:
	cd KL25Z_Debug && $(MAKE) clean
	cd PC_Debug && $(MAKE) clean
	cd KL25Z_Release && $(MAKE) clean
	cd PC_Release && $(MAKE) clean
	cd KL25Z_Debug_test && $(MAKE) clean
	cd PC_Debug_Test && $(MAKE) clean
	cd KL25Z_Release_Test && $(MAKE) clean
	cd PC_Release_Test && $(MAKE) clean
