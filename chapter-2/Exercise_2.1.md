# Exercise 2.1

Consider an animal safari game where the player can drive around in different vehicles to observe animals in the wild. Think about the different types of creatures, plants, and vehicles that might exist in such a game. How might you implement these objects in a monolithic class hierarchy object model?

Now consider the same game but implemented with a component game object model. How might you implement this? Which of these two approaches seems more beneficial for this game?

---
Well, I'd start defining the base class for vehicle, animal and plant. I can make these classes abstract & then inherent form their to create the animal. This approach may cause problems because animals have classifications the same goes for vehicle and plants, so for each classification an abstract class until reach an instantiable object. And as we can see so far, class hierarchy gets too big!

For a component approach, I'd identify the characteristics of the animal, plant or vehicle to create. After that, for each characteristic I do a component.

Finally, component approach looks much better, I just create what I need avoiding to inherit redundant things from parent classes. Farewell the component are reusable, wether I need turn on a vehicle, I use the same component to turn on a car or helicopter.
