import cv2
import matplotlib.pyplot as plt
import math
import sys

def main():
    # read in the image in 
    img = cv2.imread(sys.argv[1], cv2.IMREAD_COLOR)

    # initialize images
    logimg = img

    # displaying the original image
    cv2.imshow('image', img)
    cv2.waitKey(0)

    b, g, r = img[1, 1]

    # if the image is rgb
    if len(img.shape) == 3:
        # initialize the lists for each channel
        rcount = [0] * 256
        gcount = [0] * 256
        bcount = [0] * 256

        r2count = [0] * 32
        g2count = [0] * 32
        b2count = [0] * 32


        # loop through every pixel in the image
        for row in range(img.shape[0]):
            for col in range(img.shape[1]):
                # get the rgb values & increase the count of them
                b,g,r = (img[row, col])
                rcount[r] = rcount[r] + 1
                gcount[g] = gcount[g] + 1
                bcount[b] = bcount[b] + 1

                # get the 32 bin value and increase the count of them
                r2 = r % 32
                g2 = g % 32
                b2 = b % 32
                r2count[r2] = r2count[r2] + 1
                g2count[g2] = g2count[g2] + 1
                b2count[b2] = b2count[b2] + 1

                # calculate the log for each rgb value, account for 0
                if r != 0:
                    logr = math.log10(r/255) * 100
                else:
                    logr = 0
                if g != 0:
                    logg = math.log10(g/255) * 100
                else:
                    logg = 0
                if b != 0:
                    logb = math.log10(b/255) * 100
                else:
                    logb = 0
                # create the log image
                logimg[row, col] = logb, logg, logr


        # display the log image
        cv2.imshow('log image', logimg)
        cv2.waitKey(0)


        # plot the original rgb histogram
        plt.plot(rcount, color = 'r')
        plt.plot(gcount, color = 'g')
        plt.plot(bcount, color = 'b')
        plt.show()

        # plot the 32 bin rgb histogram
        plt.plot(r2count, color = 'r')
        plt.plot(g2count, color = 'g')
        plt.plot(b2count, color = 'b')
        plt.show()




    # if the image is grayscale
    else:
        img = cv2.imread(img, 0)

        # initialize lists
        count = [0] * 256
        x2count = [0] * 32

        # loop through all the pixels in the image
        for row in range(img.shape[0]):
            for col in range(img.shape[1]):
                # get pixel value and increase the count of that value
                x = img[row, col]
                count[x] = count[x] + 1

                # get pixel vales for 32 bins rather than 256
                x2 = x % 32
                x2count[x2] = x2count[x2] + 1

                # calculate log and create log image
                if x != 0:
                    logx = math.log10(x/255) * 100
                else:
                    logx = 0
                logimg[row, col] = logx


        # display the log image
        cv2.imshow('log image', logimg)
        cv2.waitKey(0)

        # plot the histogram
        plt.plot(count)
        plt.show()

        # plot the 32 bin histogram
        plt.plot(x2count)
        plt.show()


main()
