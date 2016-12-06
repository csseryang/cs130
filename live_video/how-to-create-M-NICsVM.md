
This one is to use a template, but will incur DNS error [vm-multiple-nics-linux](https://azure.microsoft.com/en-us/resources/templates/201-vm-multiple-nics-linux/)

I copied the code to my own repository, Then change "multinicvm" to "router1". Then it works

```
"dnsLabelPrefix": {
      "type": "string",
      "defaultValue": "multinicvm",
      "metadata": {
        "description": "Unique DNS Name for the Public IP used to access the Virtual Machine."
      }
    },
   "vmName": {
      "type": "string",
      "defaultValue": "multinicvm",
      "metadata": {
        "description": "Name of the VM"
      }
    },
```

I use the command:
```
azure config mode arm
azure group deployment create <my-resource-group> <my-deployment-name> --template-uri [my-github-url]

```
