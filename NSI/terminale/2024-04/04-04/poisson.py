#!/usr/bin/env python3
# -*- coding=utf-8 -*-
from random import expovariate


class Client:
    """
    class Client :
        À chaque création d'un nouveau client, son heure d'arrivé suit 
        la loi de probabilité voulue.
        
        lambda_ : paramètre de la loi de probailité
        « nombre de client moyen par unité de temps »
        donc si lambd = 0.1, un client tout les 10 unités de temps
    """
    temps = 0.0
    
    def __init__(self, lambda_: float):
        delta = expovariate(lambda_)
        Client.temps += delta  # on veut l’éditer pour chaque client
        self.arrivée = Client.temps
        self.guichet: float | None = None
        self.départ: float | None = None

    def temps_attente(self):
        """Renvoie le temps d’attente"""
        if self.guichet is None:
            raise ValueError("guichet is None")
        return self.guichet - self.arrivée
    
    def __repr__(self):
        arrivée_round = round(self.arrivée, 4)
        attente_round = round(self.temps_attente(), 4)
        return_str = f"Client arrivé au temps \033[32m{arrivée_round}\033[0m"
        if self.guichet is None:
            return return_str + "."
        
        guichet_round = round(self.guichet, 4)
        
        if self.départ is None:
            return_str += " et au guichet depuis le temps "
        else:
            return_str += " et au guichet des temps "
        
        if guichet_round > arrivée_round:
            temps_color = "\033[33m"
        else:
            temps_color = "\033[32m"
        return_str += temps_color
        return_str += f"{guichet_round}\033[0m "

        if self.départ is not None:
            départ_round = round(self.départ, 4)
            return_str += f"à {temps_color}{départ_round}\033[0m "
        
        return_str += "(il a attendu "
        if attente_round > 0:
            return_str += "\033[31m"
        else:
            return_str += "\033[32m"
        return_str += f"{attente_round}\033[0m)"
        return return_str


def expérience(n: int, lambda_: float, verbose: bool = False):
    """ des clients arrivent, 
        à raison d’en moyenne lambda_ client par unité de temps
        le guichet traite un client toutes les unités de temps
        on renvoie le temps moyen d’attente des n premiers clients servis        
        Par exemple expérience(100, 0.1), 100 clients arriveront 
        en à peu près 1000 unité de temps
        
        principe de la fonction
        on a 4 variables pour les clients : 
            prochain : le prochain client qui rentrera
            guichet : le client (parfois personne n’est servi)
            attente : les clients qui attendent
            finis : les clients qui ont fini
        on regarde quel est le prochain évènement et on le fait
            le nouveau client est directement servi
    """
    Client.temps = 0.0
    prochain = Client(lambda_)
    guichet: Client | None = None
    attente: list[Client] = []
    finis: list[Client] = []
    for _ in range(n+1):
        # on fait rentrer le prochain dans la file d’attente
        attente.append(prochain)
        if verbose: print(f"Temps {prochain.arrivée}: on fait rentrer le prochain dans la file")
        prochain = Client(lambda_)
        if verbose: print(f"    Le prochain prochain entrera au temps {prochain.arrivée}.")
        # on fait sortir celui au guichet
        guichet_libre = 0
        if guichet is not None:
            if verbose: print("Le guichet est déjà pris, on finit avec le client")
            assert guichet.guichet is not None
            guichet_libre = guichet.guichet + 1
            if verbose: print(f"    Le guichet est libre au temps {guichet_libre}")
            guichet.départ = guichet_libre
            finis.append(guichet)
            guichet = None
        elif verbose:
            print("Le guichet est libre")
        # on fait rentrer le prochain client au guichet
        if len(attente) != 0:
            guichet = attente.pop(0)
            if guichet_libre == 0 or guichet.arrivée > guichet_libre:
                guichet.guichet = guichet.arrivée
            else:
                guichet.guichet = guichet_libre
            if verbose: print(f"Temps {guichet.guichet}, on fait rentrer le prochain client au guichet")
            if verbose: print(f"    Il sortira au temps {guichet.guichet + 1}")
            if verbose: print(f"    Son temps d’attente était de {guichet.temps_attente()}")
        if verbose: print()
    return finis


def temps_moyen_attente(finis: list[Client]):
    """Renvoie le temps moyen d’attente"""
    if len(finis) == 0:
        return 0
    liste_temps_attente = [fini.temps_attente() for fini in finis]
    return sum(liste_temps_attente) / len(finis)


def génération():
    """
    retourne deux tableaux lambda_ et temps moyen attente, 
    pour lambda_ = 0.1, 0.2, ... 0.9
    dans un deuxième temps, trace la courbe 
    """
    tab_lambda: list[float] = []
    tab_temps_moy_attente: list[float] = []

    for lambda_times_10 in range(10):
        lambda_ = round((lambda_times_10 + 1) / 10, 1)
        tab_lambda.append(lambda_)
        tab_temps_moy_attente.append(temps_moyen_attente(expérience(10000, lambda_)))
    
    from matplotlib import pyplot as plt
    plt.plot(tab_lambda, tab_temps_moy_attente)  # type: ignore
    plt.show()  # type: ignore

    return tab_lambda, tab_temps_moy_attente
