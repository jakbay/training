import vpython as vp
import numpy as np

max_stars = 200

def ri(i = -9e15, u = 9e15):
    return np.random.random_integers(i, u)

def rd(i = 7e8, u = 1.4e14):
    return np.random.uniform(i, u)

def r_color(i = 0.8, u = 1.0):
    return vp.vector(rd(i, u), rd(i, u), rd(i, u))

def get_distance(pos1, pos2):
    return np.sqrt((pos2.x - pos1.x)**2 + (pos2.y - pos1.y)**2 + (pos2.z - pos1.z)**2)

def get_direction(pos1, pos2):
    direction = pos2 - pos1
    denominator = np.sqrt(direction.x**2 + direction.y**2 + direction.z**2)
    cosx = direction.x / denominator 
    cosy = direction.y / denominator 
    cosz = direction.z / denominator 
    return vp.vector(cosx, cosy, cosz)

def compute_acceleration(star_to_update, other_star):
    distance = get_distance(star_to_update.pos, other_star.pos)
    acceleration = (6.67e-11 * other_star.mass) / distance**2
    direction = get_direction(star_to_update.pos, other_star.pos)
    ax = direction.x * acceleration 
    ay = direction.y * acceleration
    az = direction.z * acceleration
    return vp.vector(ax, ay, az)

def update_acceleration(star_to_update, stars):
    star_to_update.acceleration = vp.vector(0, 0, 0)
    for star in stars:
        if (star != star_to_update):
            star_to_update.acceleration = star_to_update.acceleration + compute_acceleration(star_to_update, star)

def manage_collisions(star_to_update, stars):
    global max_stars
    stars_to_merge = np.empty(0)
    for star in stars:
        if (star != star_to_update):
            if (get_distance(star.pos, star_to_update.pos) <= star.radius + star_to_update.radius):
                stars_to_merge = np.append(stars_to_merge, star)
    if (stars_to_merge.size > 0):
        for star in stars_to_merge:
            if (star.mass > star_to_update.mass):
                star_tk = star
                star_tr = star_to_update
            else:
                star_tk = star_to_update
                star_tr = star
            star_tk.density = (star_tk.density * star_tk.volume + star_tr.density * star_tr.volume) / (star_tk.volume + star_tr.volume)
            star_tk.mass = star_tk.mass + star_tr.mass
            star_tk.volume = star_tk.mass / star_tk.density
            star_tk.radius = ((3 * star_tk.volume) / 4 * np.pi)**(1/3)
            star_tk.velocity = (0.8 * star_tr.mass * (star_tr.velocity - star_tk.velocity) + star_tk.mass * star_tk.velocity + star_tr.mass * star_tr.velocity) / (star_tk.mass + star_tr.mass)
            star_tk.acceleration = vp.vector(0, 0, 0)
            index = np.argwhere(stars == star_tr)
            stars = np.delete(stars, index)
            star_tr.visible = False
            del star_tr
            max_stars = max_stars - 1
    return stars


scene = vp.canvas(title = 'Binary system', width = 1900, height = 850)

stars = np.empty(0)
h0 = 2.5e-6

star_nb = 0
while star_nb < max_stars:
    star = vp.sphere(pos = vp.vector(ri(), ri(), ri()), radius = rd(), color = r_color(), make_trail = False)
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

deltaT = 1000
while star_nb > 1:
    vp.rate(20)
    i = 0
    while i < max_stars:
        stars[i].pos = stars[i].pos + stars[i].velocity * deltaT
        stars[i].pos *= 1.0 + h0 * deltaT
        update_acceleration(stars[i], stars)
        stars[i].velocity = stars[i].velocity + stars[i].acceleration * deltaT
        stars = manage_collisions(stars[i], stars)
        i = i + 1

