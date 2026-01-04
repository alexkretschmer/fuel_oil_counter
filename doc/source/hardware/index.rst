Hardware
========


The installation of the heating oil counter follows the same logic as a traditional **operating hours meter** (hour meter). 

Instead of measuring the oil flow directly with a mechanical turbine, this device is connected to the **oil burner's 230V signal line** (typically the "B4" signal on standard burner plugs). 

Fuel oil counter with Modbus (operating hours counters to calculate the fuel oil consumption). Calculation of the consumption based on the set nozzle liter consumption.

.. figure:: /gfx/block_diagram.jpg
   :alt: block diagram
   :figwidth: 80%
   :align: center


**How it works:**
*   **Signal Detection:** The counter detects when the burner is active.
*   **Calculation:** By knowing the specific nozzle throughput (gallons/liters per hour) and the measured burner runtime, the system calculates the consumed fuel with high precision.
*   **Safety:** This non-invasive method is preferred as it does not require breaking into the oil lines, significantly reducing the risk of leaks.

Connectivity
--------------

In addition to the burner signal detection, the counter is integrated into your network via **Modbus**. 

*   **Data Transmission:** The device must be connected via the Modbus interface to a separate PC, a Raspberry Pi, or directly to a **Home Assistant** instance.

.. important::
   Ensure that your Modbus gateway (e.g., USB-to-RS485 adapter) is correctly configured to communicate with the counter's registers.

Safety Warning
--------------

.. warning::
   **DANGER: 230V AC MAINS VOLTAGE!**
   
   The connection to the burner signal involves working with 230V AC electricity. 
   
   *   **Disconnect Power:** Always disconnect the heating system from the main power supply before opening any covers or touching wires.
   *   **Professional Installation:** Electrical work should only be performed by qualified personnel. 
   *   **Risk of Death:** Improper handling of mains voltage poses a serious risk of electric shock or fire.

Prototyp
---------------------

.. figure:: /gfx/oil_counter_prototyp.jpg
   :alt: Alternativtext für das Bild
   :figwidth: 80%
   :align: center


Click for downloads:

 :download:`Layout download <../../../pcb/prototyp_v10/fuil_oil_counter.brd>`.
 :download:`Shematic download <../../../pcb/prototyp_v10/fuil_oil_counter.sch>`.
