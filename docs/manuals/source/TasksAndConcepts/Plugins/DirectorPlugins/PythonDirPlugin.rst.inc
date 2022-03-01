.. _director-python-plugin:

python-dir Plugin
~~~~~~~~~~~~~~~~~

.. index::
   single: Plugin; Python; Director

The **python-dir** plugin is intended to extend the functionality of the Bareos Director by Python code. A working example is included.

-  install the **bareos-director-python-plugin** package

-  change to the Bareos plugin directory (:file:`/usr/lib/bareos/plugins/` or :file:`/usr/lib64/bareos/plugins/`)

-  copy :file:`bareos-dir.py.template` to :file:`bareos-dir.py`

-  activate the plugin in the Bareos Director configuration

-  restart the Bareos Director

-  change :file:`bareos-dir.py` as required

-  restart the Bareos Director

Loading plugins
^^^^^^^^^^^^^^^

Since :sinceVersion:`14.4.0: multiple Python plugins` multiple Python plugins can be loaded and plugin names can be arbitrary. Before this, the Python plugin always loads the file :file:`bareos-dir.py`.

The director plugins are configured in the Job-Resource (or JobDefs resource). To load a Python plugin you need

-  pointing to your plugin directory (needs to be enabled in the Director resource, too

-  Your plugin (without the suffix .py)

-  default is ’0’, you can leave this, as long as you only have 1 Director Python plugin. If you have more than 1, start with instance=0 and increment the instance for each plugin.

-  You can add plugin specific option key-value pairs, each pair separated by ’:’ key=value

Single Python Plugin Loading Example:

.. code-block:: bareosconfig
   :caption: bareos-dir.conf: Single Python Plugin Loading Example

   Director {
     # ...
     # Plugin directory
     Plugin Directory = /usr/lib64/bareos/plugins
     # Load the python plugin
     Plugin Names = "python"
   }

   JobDefs {
     Name = "DefaultJob"
     Type = Backup
     # ...
     # Load the class based plugin with testoption=testparam
     Dir Plugin Options = "python"
                          ":instance=0"
                          ":module_path=/usr/lib64/bareos/plugins"
                          ":module_name=bareos-dir-class-plugins"
                          ":testoption=testparam"
     # ...
   }

Multiple Python Plugin Loading Example:

.. code-block:: bareosconfig
   :caption: bareos-dir.conf: Multiple Python Plugin Loading Example

   Director {
     # ...
     # Plugin directory
     Plugin Directory = /usr/lib64/bareos/plugins
     # Load the python plugin
     Plugin Names = "python"
   }

   JobDefs {
     Name = "DefaultJob"
     Type = Backup
     # ...
     # Load the class based plugin with testoption=testparam
     Dir Plugin Options = "python"
                          ":instance=0"
                          ":module_path=/usr/lib64/bareos/plugins"
                          ":module_name=bareos-dir-class-plugins"
                          ":testoption=testparam1"
     Dir Plugin Options = "python"
                          ":instance=1"
                          ":module_path=/usr/lib64/bareos/plugins"
                          ":module_name=bareos-dir-class-plugins"
                          ":testoption=testparam2"
     # ...
   }

Write your own Python Plugin
^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Some plugin examples are available on https://github.com/bareos/bareos-contrib. The class-based approach lets you easily reuse stuff already defined in the baseclass BareosDirPluginBaseclass, which ships with the **bareos-director-python-plugin** package. The examples contain the plugin bareos-dir-nsca-sender, that submits the results and performance data of a backup job directly to Icinga:index:`\ <single: Icinga>`\  or
Nagios:index:`\ <single: Nagios|see{Icinga}>`\  using the NSCA protocol.