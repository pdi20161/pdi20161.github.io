split (image, channels);
equalizeHist(channels[0], channels[0]); 
equalizeHist(channels[1], channels[1]);
equalizeHist(channels[2], channels[2]);
merge(channels,equalize);
