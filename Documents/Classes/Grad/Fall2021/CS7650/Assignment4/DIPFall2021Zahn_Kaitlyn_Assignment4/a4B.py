# Part B: Histogram Equalization

# Importing all the libraries
import cv2
import numpy as np
from matplotlib import pyplot as plt
import sys

from PIL import Image

def main():
    # read in image as grayscale & convert to array
    image = cv2.imread(sys.argv[1], 0)
    image = np.asarray(image)

    # get the count of the original historgram
    count = np.zeros(256)
    for i in range(image.shape[0]):
        for j in range(image.shape[1]):
            pixel = image[i, j]
            count[pixel] += 1


    # perform histogram equalization 
    matching_csum = np.zeros(255)
    matching_csum = np.cumsum(count)
    matching_csum = matching_csum/(image.shape[0] * image.shape[1])
    M = np.round(matching_csum * 255)

    # loop through the pixels one more time and replace with equalized 
    for i in range(image.shape[0]):
        for j in range(image.shape[1]):
            pixels = image[i,j]
            image[i,j]= M[pixels]

    # display side by side show side by side reference 
    img = cv2.imread(sys.argv[1], 0)
    numpy_horizontal = np.hstack((img , image))
    cv2.imshow('Equalized Grayscale Image!', numpy_horizontal)
    cv2.waitKey(0) 
    cv2.destroyAllWindows() 

    # plot the histogram
    plt.plot(M)
    plt.show()

main()