# Folder Structure

```
TI2_Robotik
 - UebungTemplate
 - Blatt 1
    - exercise_1
       - exercise1_1.cbp
       - exercise1_1.depend
       - exercise1_1.layout
       - rest content of UebungTemplate
    - exercise_n
       - exercise1_n.cbp
       - etc
 - Blatt ...
 - Blatt n
```
One folder per exercise sheet, one subfolder per task of each sheet.
# Commits
Always commit to own branch, and request merge into main. Merge needs to be approved by other person.

# Testing Rules
Always test on the same surface that will be used in showcase. Different surfaces lead to very different turning behaviour.

# Common Error
Robot randomly resets when disconected from USB:
    -> This happen because the Motors turning leads to a huge Voltage drop, undervolting the controller leading to reset.
    -> this will not happen when debugging since the controller will always be supplied by 5V via USB
