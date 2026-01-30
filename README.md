# Coulomb's Law Simulator

A physics simulation visualizing electrostatic forces between charged particles, built in raylib.
Right now the particles self-organized into something that looks like stable molecular structures, just like ionic bonding, maybe because I added too much friction. I use the vector form of Coulomb's law to define the force: 

$$\mathbf{F} = k_e \frac{q_1 q_2}{|\mathbf{r}|^2} \mathbf{\hat{r}}$$

and then find the acceleration, velocity and position.

## Requirements

- C compiler (gcc)
- [raylib](https://www.raylib.com/) library

## Build and Run 

Clone the repo and use the provided makefile: 

```text
make build run 
```

The executable will be generated inside the bin/ directory.

## License

MIT License - feel free to use and modify!
