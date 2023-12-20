# vcu_bringup_test
code to test the [ks6e vcu](https://kennesaw-state-university-2.365.altium.com/designs/FA758309-5AB6-4595-B3EC-1B1133368B8C?variant=[No+Variations]&activeView=SCH&activeDocumentId=KS2e-VCU-rev2_PedalboxInputs.SchDoc&location=[1,95.18,27.76,42.9]#design), it will read the teensy's analog pins, toggle the digital outputs, and send CAN while also receiving.
the purpose of this code to ensure all peripherals are working, by flashing the teensy with this code and checking the serial prints for expected results
