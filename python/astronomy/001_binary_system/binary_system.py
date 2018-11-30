import vpython as vp
import numpy as np

def ri(i = -5e14, u = 5e14):
    return np.random.random_integers(i, u)

def rd(i = 7e8, u = 1.4e14):
    return np.random.uniform(i, u)

def r_color(i = 0.5, u = 1.0):
    return vp.vector(rd(i, u), rd(i, u), rd(i, u))

stars = np.empty(1)

star_nb = 0
while star_nb < 2:
    star = vp.sphere(pos = vp.vector(ri(), ri(), ri()), radius = rd(), color = r_color(), make_trail = True)
    star.velocity = vp.vector(ri(-1e10, 1e10), ri(-1e10, 1e10), ri(-1e10, 1e10))
    star.volume = 4/3 * np.pi * star.radius**3
    star.density = ri(800, 2400)
    star.mass = star.volume * star.density
    stars = np.append(stars, star)
    star_nb = star_nb + 1
    print("Star #{}".format(star_nb))
    print("Radius: {}".format(star.radius))
    print("Volume: {}".format(star.volume))
    print("Density: {}".format(star.density))
    print("Mass: {}".format(star.mass))
    print("Velocity: {}".format(star.velocity))
    print("Stars: {}".format(stars))
    print("========================")

deltaT = 1
while True:
    vp.rate(50)
    stars[0].pos = stars[0].pos + stars[0].velocity * deltaT
    stars[1].pos = stars[1].pos + stars[1].velocity * deltaT
    print("Star #1 pos: {}".format(stars[0].pos))
    print("Star #2 pos: {}".format(stars[1].pos))

