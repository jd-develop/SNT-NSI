#!/usr/bin/env python3
# coding:utf-8

class Date:
    """Représente une date : année, jour, mois.
    On suppose que le calendrier grégorien a toujours eu lieu et aura toujours lieu."""
    def __init__(self, year: int, month: int, day: int):
        self.year = year
        self.month = month
        self.day = day

        self._check_date()

    def __str__(self):
        """Renvoie la date sous sa forme française, C.-à-d. : jour, mois, année. Exemple : « 14 juillet 1789 »."""
        day = str(self.day) if self.day != 1 else "premier"
        month = self._get_french_month_name()
        year = str(self.year)
        return f"{day} {month} {year}"

    def __repr__(self):
        """Renvoie la date au format ISO, C.-à-d. : année-mois-jour. Exemple : « 1789-07-14 »."""
        return f"{self.year}-{'0' if self.month < 10 else ''}{self.month}-{'0' if self.day < 10 else ''}{self.day}"

    def _get_french_month_name(self):
        """Renvoie le nom du mois en français. Méthode privée."""
        months = ["janvier", "février", "mars", "avril", "mai", "juin", "juillet", "août", "septembre", "octobre",
                  "novembre", "décembre"]
        return months[self.month - 1]

    def _check_date(self):
        """Vérifie que la date est valide. Méthode privée."""
        assert isinstance(self.year, int), "l’année doit être entière."
        assert isinstance(self.month, int), "le mois doit être entière."
        assert isinstance(self.day, int), "le jour doit être entière."

        assert self.year != 0, "l’année 0 n’existe pas."
        assert 1 <= self.month <= 12, "le mois doit être compris entre 1 et 12."

        max_day_in_month = self._max_day_in_month()
        assert 1 <= self.day <= max_day_in_month, f"le jour doit être compris entre 1 et {max_day_in_month}."

    def _max_day_in_month(self):
        """Renvoie le jour maximum du mois. Méthode privée."""
        if self.month == 2:  # février
            if self.is_leap_year():  # années bissextiles
                return 29
            else:
                return 28
        elif self.month in [4, 6, 9, 11]:  # mois de 30 jours
            return 30
        else:
            return 31

    def is_leap_year(self):
        """Renvoie True si l’année est bissextile, False sinon.
        On rappelle qu’une année est bissextile si :
            - elle est divisible par 4
            - ET elle n’est pas divisible par 100 sauf si elle est divisible par 400.
        """
        return self.year % 4 == 0 and (self.year % 100 != 0 or self.year % 400 == 0)

    def set_year(self, year):
        self.year = year
        self._check_date()

    def get_year(self):
        return self.year

    def set_month(self, month):
        self.month = month
        self._check_date()

    def get_month(self):
        return self.month

    def set_day(self, day):
        self.day = day
        self._check_date()

    def get_day(self):
        return self.day

    def set_whole_date(self, year, month, day):
        self.year = year
        self.month = month
        self.day = day

        self._check_date()

    def get_whole_date(self) -> tuple:
        """Renvoie le tuple (année, mois, jour)"""
        return self.year, self.month, self.day

    def tomorrow(self):
        """Change la date à la date de demain."""
        self.day += 1
        max_day_in_month = self._max_day_in_month()

        if self.day > max_day_in_month:
            self.day = 1
            self.month += 1

            if self.month > 12:
                self.month = 1
                self.year += 1

                if self.year == 0:
                    self.year = 1
        return self

    def over_morrow(self):
        """Change la date à la date d’après-demain"""
        self.tomorrow()
        self.tomorrow()
        return self

    def day_after_tomorrow(self):
        """Alias de over_morrow"""
        return self.over_morrow()

    def yesterday(self):
        """Change la date à la date d’hier."""
        self.day -= 1

        if self.day == 0:
            self.month -= 1

            if self.month == 0:
                self.month = 12
                self.year -= 1

                if self.year == 0:
                    self.year = -1

            max_day_in_month = self._max_day_in_month()
            self.day = max_day_in_month
        return self

    def day_before_yesterday(self):
        """Change la date à la date d’avant-hier."""
        self.yesterday()
        self.yesterday()
        return self

    def copy(self):
        """Renvoie une copie de la date courante."""
        return Date(self.year, self.month, self.day)


date1 = Date(1789, 7, 14)
assert str(date1) == "14 juillet 1789"
assert repr(date1) == "1789-07-14"
date2 = Date(2000, 2, 29)  # normalement, pas de crash

for i in [(1900, 2, 29), (2021, 2, 29), (0, 1, 1), (1, 0, 1), (1, 1, 0), (1, 13, 1), (1, 1, 32)]:
    try:
        date3 = Date(*i)
        print(f"Erreur dans la vérification de la validité de la date {i} !")
    except AssertionError:
        print(f"Vérification OK pour la date invalide {i}")

assert date1.copy().tomorrow().get_whole_date() == (1789, 7, 15)
assert date1.copy().yesterday().get_whole_date() == (1789, 7, 13)

assert Date(1, 1, 1).yesterday().get_whole_date() == (-1, 12, 31)
assert Date(2004, 3, 1).yesterday().get_whole_date() == (2004, 2, 29)
assert Date(2005, 3, 1).yesterday().get_whole_date() == (2005, 2, 28)
assert Date(10000, 1, 1).yesterday().get_whole_date() == (9999, 12, 31)

assert Date(-1, 12, 31).tomorrow().get_whole_date() == (1, 1, 1)
assert Date(2004, 2, 28).tomorrow().get_whole_date() == (2004, 2, 29)
assert Date(2004, 2, 29).tomorrow().get_whole_date() == (2004, 3, 1)
assert Date(2005, 2, 28).tomorrow().get_whole_date() == (2005, 3, 1)
assert Date(9999, 12, 31).tomorrow().get_whole_date() == (10000, 1, 1)
