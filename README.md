# Anisotropic Diffusion :rocket:
In image processing and computer vision, anisotropic diffusion, also called Perona–Malik diffusion, is a technique aiming at reducing image noise without removing significant parts of the image content, typically edges, lines or other details that are important for the interpretation of the image. Anisotropic diffusion resembles the process that creates a scale space, where an image generates a parameterized family of successively more and more blurred images based on a diffusion process. Each of the resulting images in this family are given as a convolution between the image and a 2D isotropic Gaussian filter, where the width of the filter increases with the parameter. This diffusion process is a linear and space-invariant transformation of the original image. Anisotropic diffusion is a generalization of this diffusion process: it produces a family of parameterized images, but each resulting image is a combination between the original image and a filter that depends on the local content of the original image. As a consequence, anisotropic diffusion is a non-linear and space-variant transformation of the original image.

Although the resulting family of images can be described as a combination between the original image and space-variant filters, the locally adapted filter and its combination with the image do not have to be realized in practice. Anisotropic diffusion is normally implemented by means of an approximation of the generalized diffusion equation: each new image in the family is computed by applying this equation to the previous image. Consequently, anisotropic diffusion is an iterative process where a relatively simple set of computation are used to compute each successive image in the family and this process is continued until a sufficient degree of smoothing is obtained.

**Source code output**

![alt text](https://github.com/MorcilloSanz/AnisotropicDiffusion-Image/blob/main/img/img.png)  

**References**

Original paper: https://ieeexplore.ieee.org/document/56205

https://en.wikipedia.org/wiki/Anisotropic_diffusion

## Formal Definition

Let $\Omega \subset \mathbb{R}^{2}$ denote a subset of the plane and $I(\cdot, t) : \Omega \rightarrow \mathbb{R}$ be a be a family of gray scale images. Then anisotropic diffusion is defined as:

```math
$$\frac{\partial I}{\partial t} = \nabla \cdot \left[ c(\left|| \nabla I\right||) \nabla I \right] = \nabla c \cdot \nabla I + c(\left|| \nabla I\right||) \Delta I$$
```

Where $\Delta$ denotes the Laplacian, $\nabla$ denotes the gradient, $\nabla \cdot$ is the divergence and $c(x)$ is the diffusion coefficient which controls the rate of diffusion and is usually chosen as a function of the image gradient so as to preserve edges in the image, $t$ represents each iteration, being $I(\cdot,0)$ the input image. For $t>0$, the output image is available as $I(\cdot,t)$ with larger $t$ producing blurrier images.

## Discretization

Discrete Laplace operator is often used in image processing e.g. in edge detection and motion estimation applications. The discrete Laplacian is defined as the sum of the second derivatives Laplace operator Coordinate expressions and calculated as sum of differences over the nearest neighbours of the central pixel. Since derivative filters are often sensitive to noise in an image, the Laplace operator is often preceded by a smoothing filter (such as a Gaussian filter) in order to remove the noise before calculating the derivative. The smoothing filter and Laplace filter are often combined into a single filter.

[Discrete Laplace Operator](https://en.wikipedia.org/wiki/Discrete_Laplace_operator)

The diffusion equation can be discretized on a square lattice, with brightness values associated to the vertices, and conduction coefficients to the arcs. A 4-nearest neighbors discretization of the Lapalacian operator can be used:

>This is the final equation which we have to solve

```math
$$I^{t+1}_{i,j} = I^{t}_{i,j} + \lambda \left[ c_{N} \cdot \triangledown_{N}I + c_{S} \cdot \triangledown_{S}I + c_{E} \cdot \triangledown_{E}I + c_{W} \cdot \triangledown_{W}I \right]^{t}_{i,j}$$
```

Where $0 \leq \lambda \leq \frac{1}{4}$

## Function for the diffusion coefficient

the constant $k$ controls the sensitivity to edges and is usually chosen experimentally or as a function of the noise in the image. The diffusion coefficient is given by:

```math
$$c(x) = e^{-\left( \frac{x}{k} \right)^{2}}$$
```

In order to get the differences, we get the color increment from the neighboring pixels in four directions (North, South, East and West)

```math
$$\triangledown_{N}I^{t}_{i, j} \equiv  I^{t}_{i, j - 1} - I^{t}_{i, j}$$
```
```math
$$\triangledown_{S}I^{t}_{i, j} \equiv  I^{t}_{i, j + 1} - I^{t}_{i, j}$$
```
```math
$$\triangledown_{E}I^{t}_{i, j} \equiv  I^{t}_{i + 1, j} - I^{t}_{i, j}$$
```
```math
$$\triangledown_{W}I^{t}_{i, j} \equiv  I^{t}_{i - 1, j} - I^{t}_{i, j}$$
```

For each difference, we need a diffusion coefficient that will be multiplied by in the final equation:

```math
$$c^{t}_{N_{i, j}} = c \left(|\triangledown_{N}I^{t}_{i, j}|\right)$$
```
```math
$$c^{t}_{S_{i, j}} = c \left(|\triangledown_{S}I^{t}_{i, j}|\right)$$
```
```math
$$c^{t}_{E_{i, j}} = c \left(|\triangledown_{E}I^{t}_{i, j}|\right)$$
```
```math
$$c^{t}_{W_{i, j}} = c \left(|\triangledown_{W}I^{t}_{i, j}|\right)$$
```

In the edges, the color variation is bigger and as the color variation becomes bigger, $c$ becomes smaller, so the product between $c$ and the color variation approximates to $0$. When this happens, $I_{t+1} = I_{t} + \lambda \cdot 0$, and those pixels from the edge are the same as before. This is why the anisotropic diffusion makes edges sharper.

## See also
[Diffusion equation](https://en.wikipedia.org/wiki/Diffusion_equation)

[Heat equation](https://en.wikipedia.org/wiki/Heat_equation)
