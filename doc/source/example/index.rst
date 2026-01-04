Example for Openhab
====================

I've managed to get my oil meter into openHAB. The integration is a bit of a workaround and not yet ideal, but it’s functional for the time being.

Example for my openhab rule:

.. literalinclude:: modbus.rules
   :language: shell
   :linenos:

Example for my openhab things:

.. literalinclude:: modbus.things
   :language: shell
   :linenos:

Example for my openhab items:

.. literalinclude:: modbus.items
   :language: shell
   :linenos:

The integrated data can then be displayed on any openHAB dashboard, providing a clear overview of the remaining oil and heating trends.

.. figure:: /gfx/open_hab_example.png
   :alt: openhab example
   :figwidth: 80%
   :align: center


.. figure:: /gfx/open_hab_example_holiday.png
   :alt: openhab example
   :figwidth: 80%
   :align: center