/*
This is a patchable tool, at this stage primarily for creating different types of filters and for patching them together:
KNOWN ISSUES: The boxes will overlap and when they do its difficult to uncouple them again.


Instructions: 
- First create an audio source, this takes the input sample that has already been set
- Final output is what access the sample we are outputting to the soundcard
- comb filter is a type delay filter
- all-pass filter is a type of delay filter
- Click on the delete button and then on a box to delete it

Patching:
Click on a box, then on the box you want to patch to.
Reset patching by clicking on "empty space"."
Example:
audioSource -> combFilter -> all-passFilter -> finalOutput
Be warned that when youve created an object you will still be storing that objects pointer, so make sure youre clicking on empty space to reset the patching.

Parameters:
Each object has its own parameters. FinalOutput and AudioSource objects only have a volume control. All-Pass and CombFilters have a delaytime you can set.

*/
