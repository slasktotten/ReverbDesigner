
/*
The memory leak came from the creation of new DrawObjects. Originally when adding a new drawObject, the drawObject would just take an object, not a pointer to an object. So when I was using "new" I ended up doing this:
drawObject.push_back(*new DrawObject(*reverb->filters.back(), allPassHighlight, allPassIdle));

The problem is that the drawObject stores a copy of the original DrawObject that is created by using new and thus the pointer to the original object is lost. 
Memory leak, crash, undefined behaviour very bad.
Furthermore, because the constructor is also taking a reference to another object: *reverb->filters.back(), it means we suddenly have two objects referencing a third, one of which we've lost.

Because we are creating a few of these drawObjects, it only becomes more dangerous the longer we use the program.
*/
