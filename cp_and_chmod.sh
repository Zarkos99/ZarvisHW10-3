echo "Copying to /usr/lib/cgi-bin..."
sudo cp myLED.cgi /usr/lib/cgi-bin/
echo "Done"
echo
echo "Adjusting permissions..."
sudo chmod +s /usr/lib/cgi-bin/myLED.cgi
echo "Done"
echo
