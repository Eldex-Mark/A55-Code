
//Events:

enum {
    GUI_TO_BACKEND_EVENT__Burn_in_the_Test_button,
    GUI_TO_BACKEND_EVENT__Next_button, //on Initial Setup screen, if event needed at all to save (I added a variable to set/request that first init was done already)

    GUI_TO_BACKEND_EVENT__Select_Options_Ok_button, //if event needed at all to save

    GUI_TO_BACKEND_EVENT__Generic_Password__Ok_button, //if event needed at all to save

    GUI_TO_BACKEND_EVENT__Up_button,
    GUI_TO_BACKEND_EVENT__Down_button,
    GUI_TO_BACKEND_EVENT__Purge_button,
    GUI_TO_BACKEND_EVENT__StartStop_button,

    //GUI_TO_BACKEND_EVENT__Dispense_button, //no such button
    //GUI_TO_BACKEND_EVENT__Dispense_toggle, //needed? no such switch/checkbox (except mode-settting dropdown on Pump Settings screen)

    GUI_TO_BACKEND_EVENT__FactoryReset,

    GUI_TO_BACKEND_EVENT__Rinse_button,
    GUI_TO_BACKEND_EVENT__Reset_button,
    GUI_TO_BACKEND_EVENT__Zero_Press_Transducer_button,
    GUI_TO_BACKEND_EVENT__Sensor_Home_Button,

    GUI_TO_BACKEND_EVENT__WiFi_Connect,
    GUI_TO_BACKEND_EVENT__WiFi_ForgetConnection,

    GUI_TO_BACKEND_EVENT__Run_Self_Test_button,
    GUI_TO_BACKEND_EVENT__Save_To_Flash_drive_button,

    GUI_TO_BACKEND_EVENT__Update_on_the_web_Button,
    GUI_TO_BACKEND_EVENT__Update_from_flash_drive_button,

    GUI_TO_BACKEND_EVENT__AMOUNT //must be last
};


//Initial Set-Up (Factory Menu) screen:
//This screen sets up basic pump and device settings. These settings will be set in the factory. This screen comes up
//the first time when powered up in the factory. In the future, the user needs to enter the User password (defined in
//the user manual) to reach this screen from the Advanced settings screen. The backend will auto detect the number
//of the pumps. To change the serial, model number, and Purchase setting the user needs to enter the secret Factory
//Password, which is only known by the factory.

//Factory Test button (Originally: „Factory Burn In Test”):
//-Placeholder for future factory test, so it does nothing yet.
//-Popup prompt? („Do you want to perform a Factory burn-in test?”, „Yes”, „No”)
//-A pop-up window („The factory test has been completed”, „Ok”
//Event: Factory Defaults button (Reset to Factory)
//Event: Burn in Test button (Factory Burn In?) Placeholder for future functionality

//Change Remote Password button: text password that can be used for remote connection.
//-On click, it will show the General Password Screen to change the password.

//Select Options button: it navigates to the Purchase Settings Screen.
//-After the first appearance of this screen, the modification of this field is Factory password-protected. The Number Password screen will appear to check the password first..

//Next button: navigates to the Home screen or the next pump
//Event: Next button  //Event: Save the initial settings



//General password Screen:
//This screen is used to change the Remote password and enter the Factory password. This screen can work in 2 modes:
//-Password check
//-Password modification
//Title “Change Remote password” / “Factory password required”
//Password field label: static text be: “Enter new Remote password” / “Enter Factory password
//Event?: Ok Button: it saves the new password, then navigates back to the previous screen



//Select Options (Purchase Settings) screen:
//This screen is used to set up the purchase settings when the device has started for the first time in the factory. These
//settings can be modified later using the Factory password.
//Event?: Ok button: saves the settings  (at the moment the settings are written directly to backend variables)



//Home 1-Pump (Pump Control) screen:
//This screen controls Pump 1 and displays the header and the main menu.
//In the case of remote control: controls are disabled on this screen, except the Purge button. Remote control can be
//enabled/disabled by each pump individually.

//Up button 1,2,3 //Do we need more than 1 Up/Down/Purge/Run/Stop buttons?
//Down button 1,2,3
//Purge button 1,2,3 //Purge button: Runs purge routine. This Event triggers the pump to turn on at a specific Flow rate for a set amount of time. It is used to pull fluid from the reservoir and purge out any air in the lines and the head. The duration is 20-30 seconds.
//-Popup (“Do you want to start the purge process”, “Confirm”, “Cancel”)
//-During this process, we need a modal popup that disables every other control and we need a cancel button on that.
//Event: Run/Stop (Start/Stop) button 1,2,3
//Event?: Purge
//Event?: Dispense button (where is the button what spec says?)
//Event?: Dispense toggle (where is the button what spec says?)



//Pump Settings screen:
//On this screen, we find advanced configuration options for each pump.
//Calibrate?



//Advanced Setup screen (leads to other setup-screens):
//Settings of alarms, units of measure, and others. We can see the settings menu here too.

//Event?: Factory Menu button: A password pop-up screen („Please enter User Password”, „OK”), then Navigates to the Initial Setup (Factory Settings) screen. This is a burn-in user password (will be undocumented in the manual)
//Event?: Factory Reset button (Originally „Reset to Factory Defaults”): -Popup: Are you sure you really want to reset the pump and advanced settings to factory default? (This operation doesn’t affect the factory settings on this screen)
//                                                                       -We need an interruption here , -Pop-up window: „The factory settings have been restored successfully” , -We need to navigate to the main screen after this operation



//Firmware Update (Advanced Setup 1) screen:
//An online and offline software update option

//Event?: Update on the web Button (Check for Update)  //We need to detail better  //Check for Update on the web: It will check a specific URL about the latest version. We will need some popups about the possible errors.
                                                 //Popup at the end: („The firmware has been successfully updated”, „OK”), Or Popup(„No internet connection”, „OK”), Or in case of any other error: Popup(„Error: ERROR_MESSAGE”, „OK”)
//Update from flash drive button (Update From Flash)  //We need to detail better //Update from flash drive: we need this option because the users don’t always have an internet connection. It will search for a specific filename.
        //If the file could not be found: Popup („The installer file „optos_firmware_installer” could not be found in the root of the flash drive”, „OK”).
        //-Popup at the end in case of success: („The firmware has been successfully updated”, „OK”)., -Or Popup(„No Flash drive found”, „OK”), -Or in case of any other error: Popup(„Error: ERROR_MESSAGE”, „OK”)



//Maintenance (Advanced Setup 2) screen:
//This screen shows the working hours of the parts to help maintain them.
//Pump selector selector: we need to select the pump to set alarms on

//If the Optos pump is fitted with the “Plus” option, a pressure transducer is present in the damper assembly. The pressure transducer is sensitive to temperature changes and can read a pressure when no pressure is present.
//It is possible to re-zero the pressure transducer. Be sure to do this when there is no pressure on the pump.
//Event: Zero Pressure Transducer  //Zero Press Transducer: Resets the ambient pressure to 0. This operation affects all the pumps. It is just 1 signal on the backend.
                                   //Poup: Ambient pressure is successfully reset to 0 or failed..., so we wait for feedback from the backend. The feedback must be immediate

//Event: Pump Home / Sensor Home: Moves motor to the home position. This operation affects all the pumps. It is just 1 signal on the backend. //The piston can be sent to the fully forward position, useful when changing piston seals. The motor will drive the piston to the home position.
                                  //Popup with success or failed to find the home position, so we wait for feedback from the backend. The feedback must be immediate
//Event?: Rinse button: runs washport on all pumps immediately for 30 seconds. This button should be disabled for 30 seconds. after the user clicks on it.
//Event?: Reset button: Set the value of the “Seal Run Time” or the “Check Valve Run TIme” to 0. The customer would press this after replacing the part. So this reset button will reset the total hours the actual part of the pump has been running.
//                      (Reset Piston Seal and Reset Check Valve events, but based on the part-selection a single button is enough, which sends one of these events)
//Reset Data to Factory Default (isn't it the same as on Initial Set-Up screen? - yes, and it's only there according to the current spec.



//Communication / WiFi screen:
//Event: Connect button: connects to the selected network or the SSID (in case the hidden network is on) using the password
//Event?: Forget button: forgets the selected network



//Self Test (Advanced Setup 5) screen:
//On this screen, we can start a self-test and see the results of it.
//Event: -Run Self-Test Button: Starts the self-test. Froze the screen while the process except the scrollbar. Popup at the end: „The test has ended” with an OK button
//Event: -Save to Flash Drive button: It only appears after the test ends. This button will be enabled only after the test has ended. After the save show a popup: („The output of the test has successfully saved on the root of the flash drive with this name: optos_test_log.txt”, „Ok”)

