package com.example.lab2.Controller;


import com.example.lab2.Model.Film;
import com.example.lab2.Model.FilmForm;
import lombok.extern.slf4j.Slf4j;
import org.springframework.beans.factory.annotation.Value;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.*;
import org.springframework.web.servlet.ModelAndView;

import java.util.ArrayList;
import java.util.List;

@Slf4j
@Controller
public class FilmController {

    private static List<Film> films = new ArrayList<Film>();

    static {
        films.add(new Film("Cyberstalker", "about student which he doing cyberstalking"));
        films.add(new Film("Harry Potter", "magic school"));
    }

    @Value("${welcome.message}")
    private String message;

    @Value("${error.message}")
    private String errorMessage;


    @GetMapping(value={"/", "/index"})
    public ModelAndView index(Model model) {
        ModelAndView modelAndView = new ModelAndView();
        modelAndView.setViewName("index");
        model.addAttribute("message", message);

        return modelAndView;
    }

    @GetMapping(value = "/allfilms")
    public ModelAndView personalList(Model model) {
        ModelAndView modelAndView = new ModelAndView();
        modelAndView.setViewName("filmlist");
        model.addAttribute("films", films);

        return modelAndView;
    }

    @GetMapping(value = {"/addfilm"})
    public ModelAndView showAddFilmPage(Model model) {
        ModelAndView modelAndView = new ModelAndView("addfilm");
        FilmForm filmForm = new FilmForm();
        model.addAttribute("filmform", filmForm);

        return  modelAndView;
    }

    @PostMapping(value = {"/addfilm"})
    public ModelAndView saveFilm(Model model, @ModelAttribute("filmform") FilmForm filmForm) {
        ModelAndView modelAndView = new ModelAndView();
        modelAndView.setViewName("filmlist");

        String title = filmForm.getTitle();
        String description = filmForm.getDescription();

        if (title != null && title.length() > 0 && description != null && description.length() > 0) {
            Film newFilm = new Film(title, description);
            films.add(newFilm);
            model.addAttribute("films", films);
            return  modelAndView;
        }

        model.addAttribute("errorMessage", errorMessage);
        modelAndView.setViewName("addfilm");
        return modelAndView;
    }



    @GetMapping(value = {"/removefilm"})
    public ModelAndView showRemoveFilmPage(Model model) {
        ModelAndView modelAndView = new ModelAndView("removefilm");
        FilmForm filmForm = new FilmForm();
        model.addAttribute("filmform", filmForm);

        return  modelAndView;
    }

    @PostMapping(value = {"/removefilm"})
    public ModelAndView removeFilm(Model model, @ModelAttribute("filmform") FilmForm filmForm) {
        ModelAndView modelAndView = new ModelAndView();
        modelAndView.setViewName("filmlist");

        String title = filmForm.getTitle();

        if (title != null && title.length() > 0) {
            Film film = new Film();
            for (var f : films) {
                if (f.getTitle().equalsIgnoreCase(title)) {
                    film = f;
                    break;
                }
            }
            if (film != null) {
                films.remove(film);
                model.addAttribute("films", films);
                return modelAndView;
            }
        }

        model.addAttribute("errorMessage", errorMessage);
        modelAndView.setViewName("removefilm");
        return modelAndView;
    }

    @GetMapping(value = {"/editfilm"})
    public ModelAndView showEditFilmPage(Model model) {
        ModelAndView modelAndView = new ModelAndView("editfilm");
        FilmForm filmForm = new FilmForm();
        model.addAttribute("filmform", filmForm);

        return  modelAndView;
    }

    @PostMapping(value = {"/editfilm"})
    public ModelAndView editFilm(Model model, @ModelAttribute("filmform") FilmForm filmForm) {
        ModelAndView modelAndView = new ModelAndView();
        modelAndView.setViewName("filmlist");

        String title = filmForm.getTitle();
        String description = filmForm.getDescription();


        if (title != null && title.length() > 0) {
            for (var f : films) {
                if (f.getTitle().equalsIgnoreCase(title)) {
                    f.setDescription(description);
                    model.addAttribute("films", films);
                    return modelAndView;
                }
            }
        }

        model.addAttribute("errorMessage", errorMessage);
        modelAndView.setViewName("editfilm");
        return modelAndView;
    }
}
