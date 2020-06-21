switch (key) {
case SPACE:
	for (gal->missile = user_y_end - 1; gal->missile > 0; gal->missile--) {
		Sleep(missile_velocity);
		gotoxy(gal->flight_x, gal->missile);
		puts("¢¼");
		if (gal->missile < user_y_end - 1) {
			gotoxy(gal->flight_x, gal->missile + 1);
			puts(" ");
		}
		if (gal->missile == user_y_start) {
			gotoxy(gal->flight_x, gal->missile);
			puts(" ");
		}
	}
	break;
default:
	break;