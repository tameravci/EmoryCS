
/* ======================================================
     **** Do not change anything in this program ****
   ====================================================== */

import java.awt.*;
import java.awt.image.*;


/* ========================================================
   Coordinate system of a Canvas:

           0    1       col#
           +----+--------+----------+
           |                        |  ^
         1 |                        |  |
           |                        |  |
           |                        |  |  height
      row# |        (row#,col#)     |  |
           |                        |  |
           |                        |  |
           +------------------------+  v
            <---------------------->
                    width
   ======================================================== */

public class MyCanvas extends Canvas
{
    int MAX_WIDTH;
    int MAX_HEIGHT;

    /* -------------------------------------------------
       This variable is the 2-dim. array of pixels 
        (= image) used for the drawing
       ------------------------------------------------- */
    public BufferedImage Image;


    /* -----------------------------------------
       This method create variables to draw
       ----------------------------------------- */
    public MyCanvas(int width, int height)
    {
       MAX_WIDTH = width;
       MAX_HEIGHT = height;

       Image = new BufferedImage(MAX_WIDTH, MAX_HEIGHT, 
				 BufferedImage.TYPE_INT_RGB);
    }

    /* =====================================================
       This method copies the "image" stored in 
       the variable "pixel" onto the Canvas 

       This make drawing easier: you set up the image
       inside the variable "pixel" and then call this 
       method to make the image visible on screen
       ===================================================== */
    public void draw(int[][] pixel)
    {
       for ( int row = 0; row < MAX_HEIGHT; row++ )
          for ( int col = 0; col < MAX_WIDTH; col++ )
              Image.setRGB( col, row, pixel[col][row] );
    }

    /* -----------------------------------------------------------
       repaint will invoke paint() and will draw the pixels in
       the variable "Image"
       ----------------------------------------------------------- */
    public void paint(Graphics g)
    {
        g.drawImage(Image, 0, 0, Color.white, null);
    }

    /* ----------------------------------------------
       This update() method will eliminate flicker
       ---------------------------------------------- */
    public void update(Graphics g)
    {
       paint(g);
    }
}

