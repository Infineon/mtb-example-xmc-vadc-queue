# XMC&trade; MCU: VADC queue

This code example demonstrates how to convert multiple channels in a dedicated sequence using the queue source in VADC.

## Requirements

- [ModusToolbox&trade; software](https://www.infineon.com/cms/en/design-support/tools/sdk/modustoolbox-software/) v3.4 or later (tested with v3.4)
- [SEGGER J-Link software](https://www.segger.com/downloads/jlink/#J-LinkSoftwareAndDocumentationPack)
- Programming language: C
- Associated parts: All [XMC&trade; MCU](https://www.infineon.com/cms/en/product/microcontroller/32-bit-industrial-microcontroller-based-on-arm-cortex-m/) parts

## Supported toolchains (make variable 'TOOLCHAIN')

- GNU Arm&reg; Embedded Compiler v11.3.1 (`GCC_ARM`) - Default value of `TOOLCHAIN`

## Supported kits (make variable 'TARGET')

- [Boot Kit XMC1400](https://www.infineon.com/cms/en/product/evaluation-boards/kit_xmc14_boot_001/) (`KIT_XMC14_BOOT_001`) - Default value of `TARGET`
- [Boot Kit XMC1200](https://www.infineon.com/cms/en/product/evaluation-boards/kit_xmc12_boot_001/) (`KIT_XMC12_BOOT_001`)
- [Boot Kit XMC1300](https://www.infineon.com/cms/en/product/evaluation-boards/kit_xmc13_boot_001/) (`KIT_XMC13_BOOT_001`)
- [XMC4200 Platform2Go](https://www.infineon.com/cms/en/product/evaluation-boards/kit_xmc_plt2go_xmc4200/) (`KIT_XMC_PLT2GO_XMC4200`)
- [XMC4300 Relax EtherCAT&reg; Kit](https://www.infineon.com/cms/en/product/evaluation-boards/kit_xmc43_relax_ecat_v1/) (`KIT_XMC43_RELAX_ECAT_V1`)
- [XMC4400 Platform2Go](https://www.infineon.com/cms/en/product/evaluation-boards/kit_xmc_plt2go_xmc4400/) (`KIT_XMC_PLT2GO_XMC4400`)
- [XMC4500 Relax Kit](https://www.infineon.com/cms/en/product/evaluation-boards/kit_xmc45_relax_v1/) (`KIT_XMC45_RELAX_V1`)
- [XMC4700 Relax Kit](https://www.infineon.com/cms/en/product/evaluation-boards/kit_xmc47_relax_v1/) (`KIT_XMC47_RELAX_V1`)
- [XMC4800 Relax EtherCAT Kit](https://www.infineon.com/cms/en/product/evaluation-boards/kit_xmc48_relax_ecat_v1/) (`KIT_XMC48_RELAX_ECAT_V1`)

## Hardware setup

This example uses the board's default configuration. See the kit user guide to ensure that the board is configured correctly.

This example uses four analog input channels. [Table 1](#Table-1-Analog-module-connections-in-XMC1200-XMC1300-andXMC1400-boot-kits), [Table 2](#Table-2-Analog-module-connections-in-XMC4400-XMC4500-XMC4700-and-XMC4800-kits), [Table 3](#Table-3-Analog-module-connections-in-XMC4200-kits) and [Table 4](#Table-4-Analog-module-connections-in-XMC4300-kits) show the analog module connections.

#### Table 1. Analog module connections in XMC1200, XMC1300, and XMC1400 boot kits

**ADC channel**            | **Analog input**
---------------------------|------------------
VADC group 0 channel 1 |    Port P2.8
VADC group 0 channel 3 |    Port P2.10
VADC group 0 channel 5 |    Port P2.0

#### Table 2. Analog module connections in XMC4400, XMC4500, XMC4700 and XMC4800 kits

**ADC channel**          | **Analog input**
-------------------------------------|------------------
VADC group 0 channel 1      |    Port P14.1
VADC group 0 channel 3      |    Port P14.3
VADC group 0 channel 5      |    Port P14.5

#### Table 3. Analog module connections in XMC4200 kits

**ADC channel**          | **Analog input**
-------------------------------------|------------------
VADC group 0 channel 1      |    Port P14.1
VADC group 0 channel 4      |    Port P14.4
VADC group 0 channel 5      |    Port P14.5

#### Table 4. Analog module connections in XMC4300 kits

**ADC channel**          | **Analog input**
-------------------------------------|------------------
VADC group 0 channel 1      |    Port P14.1
VADC group 0 channel 2      |    Port P14.2
VADC group 0 channel 4      |    Port P14.4

**Note:**
XMC4200 doesn't have pin P14.1 routed, the example uses P14.7 instead (using channel 7 as Alias Value for Conversion Requests on channel 1).

**Note:**
If any analog input is left floating in XMC4500, XMC4700 and XMC4800 kits, it may return random ADC conversion values due to noise pick-up.

See the "Analog module connections" section in the [XMC1000 family technical reference manuals](https://www.infineon.com/cms/en/product/microcontroller/32-bit-industrial-microcontroller-based-on-arm-cortex-m/32-bit-xmc1000-industrial-microcontroller-arm-cortex-m0/#document-group-myInfineon-44) and [XMC4000 family technical reference manuals](https://www.infineon.com/cms/en/product/microcontroller/32-bit-industrial-microcontroller-based-on-arm-cortex-m/32-bit-xmc4000-industrial-microcontroller-arm-cortex-m4/#document-group-myInfineon-44) for more information.

## Software setup

Install a terminal emulator if you do not have one. Instructions in this document use [Tera Term](https://teratermproject.github.io/index-en.html).

This example requires no additional software or tools.

## Using the code example

Create the project and open it using one of the following:

<details open><summary><b>In Eclipse IDE for ModusToolbox&trade; software</b></summary>

1. Click the **New Application** link in the **Quick Panel** (or, use **File** > **New** > **ModusToolbox Application**). This launches the [Project Creator](https://www.infineon.com/ModusToolboxProjectCreator) tool

2. Pick a kit supported by the code example from the list shown in the **Project Creator - Choose Board Support Package (BSP)** dialog

   When you select a supported kit, the example is reconfigured automatically to work with the kit. To work with a different supported kit later, use the [Library Manager](https://www.infineon.com/ModusToolboxLibraryManager) to choose the BSP for the supported kit. You can use the Library Manager to select or update the BSP and firmware libraries used in this application. To access the Library Manager, click the link from the **Quick Panel**

   You can also just start the application creation process again and select a different kit

   If you want to use the application for a kit not listed here, you may need to update the source files. If the kit does not have the required resources, the application may not work

3. In the **Project Creator - Select Application** dialog, choose the example by enabling the checkbox

4. (Optional) Change the suggested **New Application Name**

5. The **Application(s) Root Path** defaults to the Eclipse workspace which is usually the desired location for the application. If you want to store the application in a different location, you can change the *Application(s) Root Path* value. Applications that share libraries should be in the same root path

6. Click **Create** to complete the application creation process

For more details, see the [Eclipse IDE for ModusToolbox&trade; software user guide](https://www.infineon.com/MTBEclipseIDEUserGuide) (locally available at *{ModusToolbox&trade; software install directory}/ide_{version}/docs/mtb_ide_user_guide.pdf*).

</details>

<details open><summary><b>In command-line interface (CLI)</b></summary>

ModusToolbox&trade; software provides the Project Creator as both a GUI tool and the command line tool, "project-creator-cli". The CLI tool can be used to create applications from a CLI terminal or from within batch files or shell scripts. This tool is available in the *{ModusToolbox&trade; software install directory}/tools_{version}/project-creator/* directory.

Use a CLI terminal to invoke the "project-creator-cli" tool. On Windows, use the command line "modus-shell" program provided in the ModusToolbox&trade; software installation instead of a standard Windows command-line application. This shell provides access to all ModusToolbox&trade; software tools. You can access it by typing `modus-shell` in the search box in the Windows menu. In Linux and macOS, you can use any terminal application.

This tool has the following arguments:

Argument | Description | Required/optional
---------|-------------|-----------
`--board-id` | Defined in the `<id>` field of the [BSP](https://github.com/Infineon?q=bsp-manifest&type=&language=&sort=) manifest | Required
`--app-id`   | Defined in the `<id>` field of the [CE](https://github.com/Infineon?q=ce-manifest&type=&language=&sort=) manifest | Required
`--target-dir`| Specify the directory in which the application is to be created if you prefer not to use the default current working directory | Optional
`--user-app-name`| Specify the name of the application if you prefer to have a name other than the example's default name | Optional

<br>

The following example will clone the "[VADC QUEUE](https://github.com/Infineon/mtb-example-xmc-vadc-queue)" application with the desired name "VadcQueue" configured for the *KIT_XMC14_BOOT_001* BSP into the specified working directory, *C:/mtb_projects*:

   ```
   project-creator-cli --board-id KIT_XMC14_BOOT_001 --app-id mtb-example-xmc-vadc-queue --user-app-name VadcQueue --target-dir "C:/mtb_projects"
   ```

**Note:** The project-creator-cli tool uses the `git clone` and `make getlibs` commands to fetch the repository and import the required libraries. For details, see the "Project creator tools" section of the [ModusToolbox&trade; software user guide](https://www.infineon.com/ModusToolboxUserGuide) (locally available at *{ModusToolbox&trade; software install directory}/docs_{version}/mtb_user_guide.pdf*).

</details>

<details open><summary><b>In third-party IDEs</b></summary>

**Note:** Only VS Code is supported.

1. Follow the instructions from the **In command-line interface (CLI)** section to create the application, and import the libraries using the `make getlibs` command

2. Export the application to a supported IDE using the `make <ide>` command

   For a list of supported IDEs and more details, see the "Exporting to IDEs" section of the [ModusToolbox&trade; software user guide](https://www.infineon.com/ModusToolboxUserGuide) (locally available at *{ModusToolbox&trade; software install directory}/docs_{version}/mtb_user_guide.pdf*)

3. Follow the instructions displayed in the terminal to create or import the application as an IDE project

</details>

## Operation

1. Connect the board to your PC using a micro-USB cable through the debug USB connector

2. Program the board using Eclipse IDE for ModusToolbox&trade; software:

   1. Select the application project in the Project Explorer

   2. In the **Quick Panel**, scroll down, and click **\<Application Name> Program (JLink)**

3. Connect the voltage sources to the ADC channels

4. Monitor the `adc_result` array for VADC results of the channels

5. Confirm that the ADC result values are displayed on the UART terminal

   **Figure 1. ADC result values in terminal**

   ![](images/adc_result.jpg)

## Debugging

You can debug the example to step through the code. In the IDE, use the **\<Application Name> Debug (JLink)** configuration in the **Quick Panel**. For more details, see the "Program and debug" section in the [Eclipse IDE for ModusToolbox&trade; software user guide](https://www.infineon.com/MTBEclipseIDEUserGuide).

## Design and implementation

This example demonstrates how to convert multiple channels in a dedicated sequence using the queue source in VADC.

The queue FIFO is configured with channels 1, 3, and 5 in the firmware. Channels 1, 3, and 5 are configured as a refill, so the queue will be fed again with these channels after the first conversion. Channel 1 is configured with an external trigger enabled. The capture and compare unit 4 (CCU4) is used to trigger the queue periodically. The ADC results will be displayed on the UART terminal.

### Resources and settings

The project uses a custom *design.modus* file because the following settings were modified in the default *design.modus* file.

**Figure 2. USIC (UART) settings for XMC1400 boot kit**

![](images/uart-settings-1400.jpg)

<br>

**Figure 3. UART TX pin settings for XMC1400 boot kit**

![](images/tx-pin-settings-1400.jpg)

<br>

**Figure 4. UART RX pin settings for XMC1400 boot kit**

![](images/rx-pin-settings-1400.jpg)


**Figure 5. USIC (UART) settings for XMC4700 relax kit**

![](images/uart-settings.jpg)

<br>

**Figure 6. UART TX pin settings for XMC4700 relax kit**

![](images/tx-pin-settings.jpg)

<br>

**Figure 7. UART RX pin settings for XMC4700 relax kit**

![](images/rx-pin-settings.jpg)

<br>

**Figure 8. CCU40 unit configuration**

![](images/ccu40-settings.jpg)

<br>

## Related resources

Resources  | Links
-----------|----------------------------------
Code examples  | [Using ModusToolbox&trade; software](https://github.com/Infineon/Code-Examples-for-ModusToolbox-Software) on GitHub
Device documentation | [XMC1000 family datasheets](https://www.infineon.com/cms/en/product/microcontroller/32-bit-industrial-microcontroller-based-on-arm-cortex-m/32-bit-xmc1000-industrial-microcontroller-arm-cortex-m0/#document-group-myInfineon-49) <br> [XMC1000 family technical reference manuals](https://www.infineon.com/cms/en/product/microcontroller/32-bit-industrial-microcontroller-based-on-arm-cortex-m/32-bit-xmc1000-industrial-microcontroller-arm-cortex-m0/#document-group-myInfineon-44) <br> [XMC4000 family technical reference manuals](https://www.infineon.com/cms/en/product/microcontroller/32-bit-industrial-microcontroller-based-on-arm-cortex-m/32-bit-xmc4000-industrial-microcontroller-arm-cortex-m4/#document-group-myInfineon-49) <br> [XMC4000 family technical reference manuals](https://www.infineon.com/cms/en/product/microcontroller/32-bit-industrial-microcontroller-based-on-arm-cortex-m/32-bit-xmc4000-industrial-microcontroller-arm-cortex-m4/#document-group-myInfineon-44)
Development kits | [XMC&trade; eval boards](https://www.infineon.com/cms/en/product/microcontroller/32-bit-industrial-microcontroller-based-on-arm-cortex-m/#boards)
Libraries on GitHub  | [mtb-xmclib-cat3](https://github.com/Infineon/mtb-xmclib-cat3) – XMC&trade; peripheral driver library (XMCLib)
Tools | [Eclipse IDE for ModusToolbox&trade; software](https://www.infineon.com/cms/en/design-support/tools/sdk/modustoolbox-software/) – ModusToolbox&trade; software is a collection of easy-to-use software and tools enabling rapid development with Infineon MCUs, covering applications from embedded sense and control to wireless and cloud-connected systems using AIROC&trade; Wi-Fi and Bluetooth® connectivity devices.

## Other resources

Infineon provides a wealth of data at www.infineon.com to help you select the right device, and quickly and effectively integrate it into your design.

For XMC&trade; MCU devices, see [32-bit XMC™ industrial microcontroller based on Arm&reg; Cortex&reg;-M](https://www.infineon.com/cms/en/product/microcontroller/32-bit-industrial-microcontroller-based-on-arm-cortex-m/).

## Document history

Document title: *CE232709* - *XMC&trade; MCU: VADC queue*

 Version | Description of change
 ------- | ---------------------
 1.0.0   | New code example
 1.1.0   | Added support for new kits
 2.0.0   | Updated to support ModusToolbox&trade; software v3.0; CE will not be backwards compatible with previous versions of ModusToolbox&trade; software
 2.1.0   | Added support for new kits and VADC personality
 2.1.1   | Updated README
 2.2.0   | Fixed build warnings <br> Updated analog input channel configuration for all supported BSPs
------

All other trademarks or registered trademarks referenced herein are the property of their respective owners.

© 2022-2025 Infineon Technologies AG

All Rights Reserved.

### Legal disclaimer

The information given in this document shall in no event be regarded as a guarantee of conditions or characteristics. With respect to any examples or hints given herein, any typical values stated herein and/or any information regarding the application of the device, Infineon Technologies hereby disclaims any and all warranties and liabilities of any kind, including without limitation, warranties of non-infringement of intellectual property rights of any third party.

### Information

For further information on technology, delivery terms and conditions and prices, please contact the nearest Infineon Technologies Office (www.infineon.com).

### Warnings

Due to technical requirements, components may contain dangerous substances. For information on the types in question, please contact the nearest Infineon Technologies Office.

Infineon Technologies components may be used in life-support devices or systems only with the express written approval of Infineon Technologies, if a failure of such components can reasonably be expected to cause the failure of that life-support device or system or to affect the safety or effectiveness of that device or system. Life support devices or systems are intended to be implanted in the human body or to support and/or maintain and sustain and/or protect human life. If they fail, it is reasonable to assume that the health of the user or other persons may be endangered.

-------------------------------------------------------------------------------
