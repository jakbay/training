"""
    Space soup program.

        This is a simplistic simulation of 'max_stars' randomly generated and
        randomly positionned in space.
            The only forces acting on the stars are the acceleration of gravity
            provoked by each and every other stars and the expansion of space itself,
            which is not strictly speaking a force but pushes the stars away as if
            it was one.
            Whenever stars collide, they are merged into a single, bigger and heavier
            star.
            The outcome is absolutely random but generaly consists of a few smaller
            stars orbiting around a very heavy object.

        A lot of improvements could be made in the future:
            - Manage the degeneracy of matter (a star heavier than a certain mass will
              degenerate into a dwarf, a neutron star or a black hole. This can change
              the outcome of the simulation, as those objects would be very much denser,
              therefore smaller, making collisions more difficult.
            - Add a big central star in the center  of the simulated space.
            - Add an initial velocity to the objects to avoid them all crushing together
              at the same time.
            - Make the options available without having to modify the script.
            - Optimize the computation of the accelerations, as the simulation
              is very slow at the beginning.
"""

import vpython as vp
import numpy as np

# Starting number of stars.
max_stars = 200

# Generate random integer between i and u.
def ri(i = -9e15, u = 9e15):
    return np.random.random_integers(i, u)

# Generate random float between i and u.
def rd(i = 7e8, u = 1.4e14):
    return np.random.uniform(i, u)

# Generate random color, whose components range between i and u.
def r_color(i = 0.8, u = 1.0):
    return vp.vector(rd(i, u), rd(i, u), rd(i, u))

# Get absolute distance between pos1 and 2.
def get_distance(pos1, pos2):
    return np.sqrt((pos2.x - pos1.x)**2 + (pos2.y - pos1.y)**2 + (pos2.z - pos1.z)**2)

# Get a vector containing the cosines of the angles of the vector
# formed by pos1 and 2 with the normal vectors.
def get_direction(pos1, pos2):
    direction = pos2 - pos1
    denominator = np.sqrt(direction.x**2 + direction.y**2 + direction.z**2)
    cosx = direction.x / denominator 
    cosy = direction.y / denominator 
    cosz = direction.z / denominator 
    return vp.vector(cosx, cosy, cosz)

# Compute the gravitational acceleration of star_to_update relatively to other_star.
def compute_acceleration(star_to_update, other_star):
    distance = get_distance(star_to_update.pos, other_star.pos)
    acceleration = (6.67e-11 * other_star.mass) / distance**2
    direction = get_direction(star_to_update.pos, other_star.pos)
    ax = direction.x * acceleration 
    ay = direction.y * acceleration
    az = direction.z * acceleration
    return vp.vector(ax, ay, az)

# Compute the gravitational acceleration of star_to_update relatively to every other stars.
def update_acceleration(star_to_update, stars):
    star_to_update.acceleration = vp.vector(0, 0, 0)
    for star in stars:
        if (star != star_to_update):
            star_to_update.acceleration = star_to_update.acceleration + compute_acceleration(star_to_update, star)

# Check collisions and merge the stars if need be.
def manage_collisions(star_to_update, stars):
    global max_stars
    stars_to_merge = np.empty(0)
    # Check whether there are collisions.
    for star in stars:
        if (star != star_to_update):
            # There's a collision if the distance between two stars is shorter than the
            # sum of their radii.
            if (get_distance(star.pos, star_to_update.pos) <= star.radius + star_to_update.radius):
                stars_to_merge = np.append(stars_to_merge, star)
    # If collisions were detected, merge the stars.
    # Merge the lighter star into the heavier star.
    if (stars_to_merge.size > 0):
        for star in stars_to_merge:
            # Check which of is heavier and will survive.
            # tk == to keep.
            # tr == to remove.
            if (star.mass > star_to_update.mass):
                star_tk = star
                star_tr = star_to_update
            else:
                star_tk = star_to_update
                star_tr = star
            # Density of an object formed with two different objects merged.
            star_tk.density = (star_tk.density * star_tk.volume + star_tr.density * star_tr.volume) / (star_tk.volume + star_tr.volume)
            # The mass is only an addition.
            star_tk.mass = star_tk.mass + star_tr.mass
            # Density = mass / volume.
            star_tk.volume = star_tk.mass / star_tk.density
            # Inverse of the volume equation of a sphere.
            star_tk.radius = ((3 * star_tk.volume) / 4 * np.pi)**(1/3)
            # Compute the velocity of the remaining star. The crash is a little bit elastic.
            star_tk.velocity = (0.1 * star_tr.mass * (star_tr.velocity - star_tk.velocity) + star_tk.mass * star_tk.velocity + star_tr.mass * star_tr.velocity) / (star_tk.mass + star_tr.mass)
            # Resets acceleration, not too sure whether this is needed but it's perfectly harmless anyway.
            star_tk.acceleration = vp.vector(0, 0, 0)
            # Remove the merged star from the array of stars, make the sphere invisible,
            # remove the trail and delete the object.
            index = np.argwhere(stars == star_tr)
            stars = np.delete(stars, index)
            star_tr.visible = False
            star_tr.clear_trail()
            del star_tr
            # Don't forget to decrease the number of stars.
            max_stars = max_stars - 1
    return stars


scene = vp.canvas(title = 'Space soup', width = 1900, height = 850)

stars = np.empty(0)

# Used to compute the expansion of space.
h0 = 2.5e-7

star_nb = 0
while star_nb < max_stars:
    # Generate max_stars with random caracteristics (mass, density and position).
    star = vp.sphere(pos = vp.vector(ri(), ri(), ri()), radius = rd(), color = r_color(), make_trail = True, retain = 50)
    star.velocity = vp.vector(0, 0, 0)
    star.acceleration = vp.vector(0, 0, 0)
    star.volume = 4/3 * np.pi * star.radius**3
    star.density = ri(800, 2400)
    star.mass = star.volume * star.density
    stars = np.append(stars, star)
    print("Star #{}".format(star_nb))
    print("Radius: {}m".format(star.radius))
    print("Volume: {}m3".format(star.volume))
    print("Density: {}kg.m-3".format(star.density))
    print("Mass: {}kg".format(star.mass))
    print("Velocity: {}m.s-1".format(star.velocity))
    print("========================")
    star_nb = star_nb + 1

deltaT = 2000
while star_nb > 1:
    vp.rate(50)
    i = 0
    while i < max_stars:
        # Update the positions with the velocities.
        stars[i].pos = stars[i].pos + stars[i].velocity * deltaT
        # Expand space. This parameter is not absolutely necessary but
        # fine tuning it prevents the stars from falling too far towards the
        # center of gravity of the whole system.
        # If the h0 number is too high, the system will expand without ever
        # falling.
        stars[i].pos *= 1.0 + h0 * deltaT
        # Compute the acceleration of every star relatively to every
        # other star.
        update_acceleration(stars[i], stars)
        # Update the velocities with the accelerations.
        stars[i].velocity = stars[i].velocity + stars[i].acceleration * deltaT
        # Merge the stars whenever they collide.
        stars = manage_collisions(stars[i], stars)
        i = i + 1

